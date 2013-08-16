#include <cstdio>
#include <algorithm>
#include <QString>
#include <QObject>
#include <QFile>
#include <QMap>
#include <QTime>
#include <QTextStream>
#include <qmath.h>
#include "gostatus.h"
#include "goaccumulative.h"
#include "gomarkovgraph.h"
#include "gomarkovanalysis.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "gomarkovchartdata.h"
#include "gomarkovoperatorfactory.h"
#include "goinput.h"
#include "gooutput.h"
#include "gosignal.h"
#include "gomarkovcommoncause.h"
#include "messagefactory.h"
#include "messager.h"
#include "gocutset.h"
#include "gopathset.h"
#include "gopathsetset.h"
#include "gopathsetsetset.h"
#include "gomarkovoperator19.h"
using namespace std;

GOMarkovGraph::GOMarkovGraph() : GOGraph()
{
    delete this->_analysis;
    this->_analysis = new GOMarkovAnalysis();
}

GOMarkovGraph::~GOMarkovGraph()
{
    this->GOGraph::~GOGraph();
    this->_equivalent.clear();
}

QVector<GOMarkovEquivalent*> GOMarkovGraph::getEquivalent() const
{
    return this->_equivalent;
}

void GOMarkovGraph::addEquivalent(GOMarkovEquivalent *equivalent)
{
    this->_equivalent.push_back(equivalent);
}

QVector<GOMarkovCommonCause*> GOMarkovGraph::getCommonCause() const
{
    return this->_commonCause;
}

void GOMarkovGraph::addCommonCause(GOMarkovCommonCause *commonCause)
{
    this->_commonCause.push_back(commonCause);
}

void GOMarkovGraph::calcAccumulativeProbability(double time)
{
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Graph ") + this->_error;
        this->sendMessage(message);
        return;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i]->TypedItem::type() == GOMarkovOperatorFactory::Operator_Type_19)
        {
            GOMarkovOperator19 *op = (GOMarkovOperator19*)list[i];
            GOMarkovStatus prevStatus;
            prevStatus.setVectorLength(op->deltaNum());
            for (int i = 0; i < op->deltaNum(); ++i)
            {
                GOMarkovStatus status = this->calcAccumulativeProbability(time, op->ids()->at(i), op->delta()->at(i), op);
                prevStatus.setProbabilityNormal(i, status.probabilityNormal().getValue(0));
                prevStatus.setFrequencyBreakdown(i, status.frequencyBreakdown().getValue(0));
                prevStatus.setFrequencyRepair(i, status.frequencyRepair().getValue(0));
            }
            this->calcAccumulativeProbability(time, "null", 1.0, op);
            op->calcOutputMarkovStatus(prevStatus);
        }
        else
        {
            QVector<GOGraph::Output> commonList;
            if (GOMarkovOperatorFactory::isCommonPossible(list[i]->TypedItem::type()))
            {
                commonList = this->getCommonSignalList(list[i]);
            }
            if (commonList.size() == 0)
            {
                ((GOMarkovOperator*)list[i])->calcOutputMarkovStatus(time);
            }
            else
            {
                QVector<GOOperator*> commonOperator;
                QVector<int> commonIndex;
                for (int j = 0; j < commonList.size(); ++j)
                {
                    commonOperator.push_back(commonList[j].op);
                    commonIndex.push_back(commonList[j].outputIndex);
                }
                ((GOMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GOMarkovOperator*)list[i], commonOperator, commonIndex, time);
            }
        }
        GOMarkovOperator *op = (GOMarkovOperator*)list[i];
        for (int i = 0; i < op->output()->number(); ++i)
        {
            for (int j = 0; j < op->markovOutputStatus()->at(i)->probabilityNormal().length(); ++j)
            {
                if (op->markovOutputStatus()->at(i)->probabilityNormal().getValue(j) > 1.0)
                {
                    op->markovOutputStatus()->at(i)->setProbabilityNormal(j, 1.0);
                }
                else if (op->markovOutputStatus()->at(i)->probabilityNormal().getValue(j) < 0.0)
                {
                    op->markovOutputStatus()->at(i)->setProbabilityNormal(j, 0.0);
                }
            }
        }
    }
    list.clear();
}

/**
 * Calculate the accumulative probability with the probability changed with the time.
 * @param totalTime The total time of the calculation.
 * @param count The time the calculation does.
 */
GOMarkovChartData *GOMarkovGraph::calcAccumulativeProbability(double totalTime, int count)
{
    Message *message;
    QTime time;
    time.start();
    message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_CLEAR);
    this->sendMessage(message);
    message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_TEXT);
    message->paramString = "Start Analysising...";
    this->sendMessage(message);
    bool isOperatorError = false;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[i];
        if (op->errorDetect(this))
        {
            isOperatorError = true;
        }
    }
    if (isOperatorError)
    {
        return 0L;
    }
    GOMarkovChartData *data = new GOMarkovChartData();
    QVector<GOOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        GOMarkovOperator *op = (GOMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
        int outputNum = op->output()->number();
        if (outputNum == 1)
        {
            if (op->isGlobalFeedback())
            {
                data->names.push_back(QString("%1'").arg(op->id()));
            }
            else
            {
                data->names.push_back(QString("%1").arg(op->id()));
            }
            data->probabilities.push_back(QVector<DoubleVector>());
            data->lambdas.push_back(QVector<DoubleVector>());
            data->mus.push_back(QVector<DoubleVector>());
        }
        else
        {
            for (int j = 0; j < outputNum; ++j)
            {
                if (op->isGlobalFeedback())
                {
                    data->names.push_back(QString("%1' (%2)").arg(op->id()).arg(j + 1));
                }
                else
                {
                    data->names.push_back(QString("%1 (%2)").arg(op->id()).arg(j + 1));
                }
                data->probabilities.push_back(QVector<DoubleVector>());
                data->lambdas.push_back(QVector<DoubleVector>());
                data->mus.push_back(QVector<DoubleVector>());
            }
        }
    }
    for (int i = 0; i < count; ++i)
    {
        double time = i * totalTime / (count - 1);
        data->times.push_back(time);
        // Record initial value of lamda.
        QVector<DoubleVector> lamdas;
        for (int j = 0; j < list.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[j];
            op->initMarkovStatus(time);
        }
        for (int j = 0; j < list.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[j];
            lamdas.push_back(op->markovStatus()->frequencyBreakdown());
        }
        // Calculate without common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(this->_commonCause[j]->breakdownIndividual());
                op->initWithCurrentLambda(time);
            }
        }
        this->calcAccumulativeProbability(time);
        if (this->getErrorMessage() != "")
        {
            delete data;
            return 0L;
        }
        for (int j = 0, index = 0; j < list.size(); ++j)
        {
            GOMarkovOperator* op = (GOMarkovOperator*)list[j];
            int outputNum = op->markovOutputStatus()->size();
            for (int k = 0; k < outputNum; ++k)
            {
                data->probabilities[index].push_back(op->markovOutputStatus()->at(k)->probabilityNormal());
                data->lambdas[index].push_back(op->markovOutputStatus()->at(k)->frequencyBreakdown());
                data->mus[index++].push_back(op->markovOutputStatus()->at(k)->frequencyRepair());
            }
        }
        // Fixed the error caused by common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            QVector<DoubleVector> r00;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityBreakdown(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < list.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)list[k];
                for (int l = 0; l < list[k]->output()->number(); ++l)
                {
                    r00.push_back(op->markovOutputStatus()->at(l)->probabilityNormal());
                }
            }

            QVector<DoubleVector> r11;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityNormal(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < list.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)list[k];
                int outputNum = op->markovOutputStatus()->size();
                for (int l = 0; l < outputNum; ++l)
                {
                    r11.push_back(op->markovOutputStatus()->at(l)->probabilityNormal());
                }
            }

            double c12 = this->_commonCause[j]->calcCommonCause(time);
            for (int k = 0; k < r00.size(); ++k)
            {
                data->probabilities[k][i] += c12 * (r00[k] - r11[k]);
                if (data->probabilities[k][i] > 1.0)
                {
                    data->probabilities[k][i] = 1.0;
                }
            }
        }
        // Restore the lamda value.
        for (int j = 0; j < list.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[j];
            op->markovStatus()->setFrequencyBreakdown(lamdas[j]);
        }
    }

    message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_CORRECT);
    message->paramString = QString("Analysis Completed. It takes %1 seconds. ").arg(time.elapsed() / 1000.0);
    this->sendMessage(message);
    return data;
}

GOMarkovStatus GOMarkovGraph::calcAccumulativeProbability(double time, QString id, double delta, GOMarkovOperator* stopOperator)
{
    QVector<GOOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i] == stopOperator)
        {
            GOMarkovStatus *status = stopOperator->getPrevMarkovStatus();
            GOMarkovStatus res;
            res.setProbabilityNormal(status->probabilityNormal());
            res.setFrequencyBreakdown(status->frequencyBreakdown());
            res.setFrequencyRepair(status->frequencyRepair());
            return res;
        }
        if (list[i]->TypedItem::type() == GOMarkovOperatorFactory::Operator_Type_19)
        {
            GOMarkovOperator19 *op = (GOMarkovOperator19*)list[i];
            GOMarkovStatus prevStatus;
            prevStatus.setVectorLength(op->deltaNum());
            for (int i = 0; i < op->deltaNum(); ++i)
            {
                GOMarkovStatus status = this->calcAccumulativeProbability(time, op->ids()->at(i), op->delta()->at(i), op);
                prevStatus.setProbabilityNormal(i, status.probabilityNormal().getValue(0));
                prevStatus.setFrequencyBreakdown(i, status.frequencyBreakdown().getValue(0));
                prevStatus.setFrequencyRepair(i, status.frequencyRepair().getValue(0));
            }
            this->calcAccumulativeProbability(time, "null", 1.0, op);
            op->calcOutputMarkovStatus(prevStatus);
        }
        else
        {
            QVector<GOGraph::Output> commonList;
            if (GOMarkovOperatorFactory::isCommonPossible(list[i]->TypedItem::type()))
            {
                commonList = this->getCommonSignalList(list[i]);
            }
            if (commonList.size() == 0)
            {
                ((GOMarkovOperator*)list[i])->calcOutputMarkovStatus(time);
            }
            else
            {
                QVector<GOOperator*> commonOperator;
                QVector<int> commonIndex;
                for (int j = 0; j < commonList.size(); ++j)
                {
                    commonOperator.push_back(commonList[j].op);
                    commonIndex.push_back(commonList[j].outputIndex);
                }
                ((GOMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GOMarkovOperator*)list[i], commonOperator, commonIndex, time);
            }
            if (QString("%1").arg(list[i]->id()) == id)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)list[i];
                for (int i = 0; i < list[i]->output()->number(); ++i)
                {
                    op->markovOutputStatus()->at(i)->setProbabilityNormal(op->markovOutputStatus()->at(i)->probabilityBreakdown() * delta);
                    op->markovOutputStatus()->at(i)->setFrequencyBreakdown(op->markovOutputStatus()->at(i)->frequencyBreakdown() * delta);
                    op->markovOutputStatus()->at(i)->setFrequencyRepair(op->markovOutputStatus()->at(i)->frequencyRepair() * delta);
                }
            }
            GOMarkovOperator *op = (GOMarkovOperator*)list[i];
            for (int i = 0; i < op->output()->number(); ++i)
            {
                for (int j = 0; j < op->markovOutputStatus()->at(i)->probabilityNormal().length(); ++j)
                {
                    if (op->markovOutputStatus()->at(i)->probabilityNormal().getValue(j) > 1.0)
                    {
                        op->markovOutputStatus()->at(i)->setProbabilityNormal(j, 1.0);
                    }
                    else if (op->markovOutputStatus()->at(i)->probabilityNormal().getValue(j) < 0.0)
                    {
                        op->markovOutputStatus()->at(i)->setProbabilityNormal(j, 0.0);
                    }
                }
            }
        }
    }
    list.clear();
    GOMarkovStatus res;
    return res;
}

bool GOMarkovGraph::isContainCycleDfs(QVector<bool> &visit,
                                QVector<int> &dfn,
                                QVector<int> &low,
                                QVector<int> &stack,
                                int &timeStamp,
                                int u)
{
    dfn[u] = low[u] = timeStamp++;
    visit[u] = true;
    stack.push_back(u);
    GOOperator *op = this->_operator[u];
    if (op->TypedItem::type() != GOMarkovOperatorFactory::Operator_Type_21)
    {
        for (int i = 0; i < op->output()->number(); ++i)
        {
            for (int j = 0; j < op->output()->signal()->at(i)->size(); ++j)
            {
                GOOperator *next = op->output()->signal()->at(i)->at(j)->next(op);
                int v = this->_operatorPos[next];
                if (dfn[v] == -1)
                {
                    if (this->isContainCycleDfs(visit, dfn, low, stack, timeStamp, v))
                    {
                        return true;
                    }
                    if (low[v] < low[u])
                    {
                        low[u] = low[v];
                    }
                }
                else if (visit[v])
                {
                    if (dfn[v] < low[u])
                    {
                        low[u] = dfn[v];
                    }
                }
            }
        }
    }
    if (dfn[u] == low[u])
    {
        int count = 0;
        int temp;
        do
        {
            temp = stack[stack.size() - 1];
            stack.pop_back();
            visit[temp] = false;
            ++ count;
        }
        while (temp != u);
        if (count > 1)
        {
            return true;
        }
    }
    return false;
}

QVector< QVector<GOGraph::Output> > GOMarkovGraph::getAncestorList(GOOperator *op, int outputIndex, int signalIndex)
{
    Output commonSignal;
    commonSignal.op = op;
    commonSignal.outputIndex = outputIndex;
    commonSignal.signalIndex = signalIndex;
    if (op->input()->number() == 0)
    {
        QVector< QVector<Output> > vector;
        QVector<Output> list;
        list.push_back(commonSignal);
        vector.push_back(list);
        return vector;
    }
    QVector< QVector<Output> > vector;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        outputIndex = prev->output()->getSignalIndex(signal);
        for (int j = 0; j < prev->output()->signal()->at(outputIndex)->size(); ++j)
        {
            if (prev->output()->signal()->at(outputIndex)->at(j)->next(prev) == op)
            {
                signalIndex = j;
                break;
            }
        }
        QVector< QVector<Output> > pathList;
        if (prev->TypedItem::type() != GOMarkovOperatorFactory::Operator_Type_21)
        {
             pathList = this->getAncestorList(prev, outputIndex, signalIndex);
        }
        for (int j = 0; j < pathList.size(); ++j)
        {
            pathList[j].push_front(commonSignal);
            vector.push_back(pathList[j]);
        }
    }
    for (int i = 0; i < op->subInput()->number(); ++i)
    {
        GOSignal *signal = op->subInput()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        outputIndex = prev->output()->getSignalIndex(signal);
        for (int j = 0; j < prev->output()->signal()->at(outputIndex)->size(); ++j)
        {
            if (prev->output()->signal()->at(outputIndex)->at(j)->next(prev) == op)
            {
                signalIndex = j;
                break;
            }
        }
        QVector< QVector<Output> > pathList;
        if (prev->TypedItem::type() != GOMarkovOperatorFactory::Operator_Type_21)
        {
             pathList = this->getAncestorList(prev, outputIndex, signalIndex);
        }
        for (int j = 0; j < pathList.size(); ++j)
        {
            pathList[j].push_front(commonSignal);
            vector.push_back(pathList[j]);
        }
    }
    return vector;
}

GOPathSetSetSet GOMarkovGraph::findPath(int order)
{
    GOPathSetSetSet path;
    this->calcAccumulativeProbability(1e10, 2);
    if (this->_error != "")
    {
        return path;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<DoubleVector>* > normals;
    for (int i = 0; i < list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[i];
        QVector<DoubleVector> *normal = new QVector<DoubleVector>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            normal->push_back(op->markovOutputStatus()->at(i)->probabilityNormal());
        }
        normals[op->realID()] = normal;
    }
    GOPathSet tempPath;
    if (order > list.size())
    {
        order = list.size();
    }
    for (int i = 0; i < list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
    }
    for (int i = 1; i <= order; ++i)
    {
        this->findPathDfs(normals, path, list, tempPath, 0, 0, i);
    }
    for (QMap<int, QVector<DoubleVector>* >::iterator it = normals.begin(); it != normals.end(); ++it)
    {
        delete it.value();
    }
    normals.clear();
    return path;
}

GOPathSetSetSet GOMarkovGraph::findCut(int order)
{
    GOPathSetSetSet path;
    this->calcAccumulativeProbability(1e10, 2);
    if (this->_error != "")
    {
        return path;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<DoubleVector>* > fails;
    for (int i = 0; i < list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[i];
        QVector<DoubleVector> *fail = new QVector<DoubleVector>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            fail->push_back(op->markovOutputStatus()->at(i)->probabilityBreakdown());
        }
        fails[op->realID()] = fail;
    }
    GOCutSet tempPath;
    if (order > list.size())
    {
        order = list.size();
    }
    for (int i = 0; i < list.size(); ++i)
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
    }
    for (int i = 1; i <= order; ++i)
    {
        this->findCutDfs(fails, path, list, tempPath, 0, 0, i);
    }
    for (QMap<int, QVector<DoubleVector>* >::iterator it = fails.begin(); it != fails.end(); ++it)
    {
        delete it.value();
    }
    fails.clear();
    return path;
}

void GOMarkovGraph::findPathDfs(QMap<int, QVector<DoubleVector> *> &normals, GOPathSetSetSet &path, QVector<GOOperator*> &list, GOPathSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        for (int i = 0; i < list.size(); ++i)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[i];
            op->calcOutputMarkovStatus(1e10);
        }
        QVector<GOPathSetSetSet::End> ends;
        QVector<double> probabilityList;
        for (int i = 0; i < list.size(); ++i)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[i];
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (op->output()->signal()->at(j)->size() == 0)
                {
                    for (int k = 0; k < op->markovOutputStatus()->at(j)->probabilityNormal().length(); ++k)
                    {
                        if (op->markovOutputStatus()->at(j)->probabilityNormal().getValue(k) > 1.0 - 1e-8)
                        {
                            GOPathSetSetSet::End end;
                            end.op = op;
                            end.outputIndex = j;
                            end.vectorIndex = k;
                            ends.push_back(end);
                            probabilityList.push_back(normals[op->realID()]->at(j).getValue(k));
                        }
                    }
                }
            }
            for (int i = 0; i < ends.size(); ++i)
            {
                tempPath.setTotalProbablity(probabilityList[i]);
                path.add(ends[i].op, tempPath.copy(), ends[i].outputIndex, ends[i].vectorIndex);
            }
        }
        return;
    }
    if (number > order || index >= list.size())
    {
        return;
    }
    if (!((GOMarkovOperator*)list[index])->isGlobalFeedback())
    {
        if (!GOMarkovOperatorFactory::isLogical(list[index]->type()))
        {
            GOMarkovOperator* op = (GOMarkovOperator*)list[index];
            op->initMarkovStatus(1e10);
            op->markovStatus()->setProbabilityNormal(1.0);
            tempPath.add(list[index]);
            this->findPathDfs(normals, path, list, tempPath, index + 1, number + 1, order);
            tempPath.removeEnd();
        }
    }
    GOMarkovOperator* op = (GOMarkovOperator*)list[index];
    op->initMarkovStatus(1e10);
    this->findPathDfs(normals, path, list, tempPath, index + 1, number, order);
}

void GOMarkovGraph::findCutDfs(QMap<int, QVector<DoubleVector> *> &fails, GOPathSetSetSet &cut, QVector<GOOperator*> &list, GOCutSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        for (int i = 0; i < list.size(); ++i)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[i];
            op->calcOutputMarkovStatus(1e10);
        }
        QVector<GOPathSetSetSet::End> ends;
        QVector<double> probabilityList;
        for (int i = 0; i < list.size(); ++i)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)list[i];
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (op->output()->signal()->at(j)->size() == 0)
                {
                    for (int k = 0; k < op->markovOutputStatus()->at(j)->probabilityBreakdown().length(); ++k)
                    {
                        if (op->markovOutputStatus()->at(j)->probabilityBreakdown().getValue(k) > 1.0 - 1e-8)
                        {
                            GOPathSetSetSet::End end;
                            end.op = op;
                            end.outputIndex = j;
                            end.vectorIndex = k;
                            ends.push_back(end);
                            probabilityList.push_back(fails[op->realID()]->at(j).getValue(k));
                        }
                    }
                }
            }
        }
        for (int i = 0; i < ends.size(); ++i)
        {
            tempPath.setTotalProbablity(probabilityList[i]);
            cut.add(ends[i].op, tempPath.copy(), ends[i].outputIndex, ends[i].vectorIndex);
        }
        return;
    }
    if (number > order || index >= list.size())
    {
        return;
    }
    if (!((GOMarkovOperator*)list[index])->isGlobalFeedback())
    {
        if (!GOMarkovOperatorFactory::isLogical(list[index]->type()))
        {
            GOMarkovOperator* op = (GOMarkovOperator*)list[index];
            op->initMarkovStatus(1e10);
            op->markovStatus()->setProbabilityBreakdown(1.0);
            tempPath.add(list[index]);
            this->findCutDfs(fails, cut, list, tempPath, index + 1, number + 1, order);
            tempPath.removeEnd();
        }
    }
    GOMarkovOperator* op = (GOMarkovOperator*)list[index];
    op->initMarkovStatus(1e10);
    this->findCutDfs(fails, cut, list, tempPath, index + 1, number, order);
}

bool GOMarkovGraph::saveAsHTML(const QString filePath)
{
    this->_error = "";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        this->_error = QObject::tr("Can't open file ") + filePath;
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" + file.fileName() + "</title>" << endl;
    out << "<meta charset = UTF-8>" << endl;
    out << "<style>body{width:100%}table,td{margin:0 auto;border:1px solid #CCC;border-collapse:collapse;font:small/1.5 'Tahoma','Bitstream Vera Sans',Verdana,Helvetica,sans-serif;}table{border:none;border:1px solid #CCC;}thead th,tbody th{color:#666;padding:5px 10px;border-left:1px solid #CCC;}tbody th{background:#fafafb;border-top:1px solid #CCC;text-align:left;}tbody tr td{padding:5px 10px;color:#666;}tbody tr:hover td{color:#454545;}tfoot td,tfoot th{border-left:none;border-top:1px solid #CCC;padding:4px;color:#666;}caption{text-align:left;font-size:120%;padding:10px 0;color:#666;}table a:link{color:#666;}table a:visited{color:#666;}table a:hover{color:#003366;text-decoration:none;}table a:active{color:#003366;}</style>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<input type = hidden value = ZHG/>";
    QVector<GOOperator*> list;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        list.push_back(this->_operator[i]);
    }
    for (int i = 0; i < list.size(); ++i)
    {
        for (int j = i + 1; j < list.size(); ++j)
        {
            if (list[i]->id() > list[j]->id())
            {
                GOOperator *temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    out << "<h1>" + QObject::tr("Analysis Result") + "</h1>" << endl;
    for (int i = 0; i < list.size(); ++i)
    {
        out << "<table>" << endl;
        out << "<tr style='text-align: center;'>" << endl;
        out << "<th>";
        out << QString("%1-%2").arg(list[i]->type()).arg(list[i]->id()) << endl;
        out << "</th>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>";
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Operator") + "</th>" << endl;
        out << "<th>" + QObject::tr("Output") + "</th>" << endl;
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j < list[i]->status()->number(); ++j)
        {
            out << "<tr>" << endl;
            out << QString("<td style='text-align:center;'>%1</td>").arg(j);
            out << "<td>" << list[i]->status()->probability(j) << "</td>";
            out << "</tr>" << endl;
        }
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyBreakdown().getValue(0) << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyRepair().getValue(0) << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << QString("<td>Normal</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityNormal().getValue(0)) << endl;
        out << QString("<td>Breakdown</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityBreakdown().getValue(0)) << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown().getValue(0) << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown().getValue(0)) << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair().getValue(0) << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair().getValue(0)) << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "</td>";
        out << "</tr>" << endl;
        out << "</table>" << endl;
        out << "<br/>" << endl;
    }
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}

bool GOMarkovGraph::saveAsHTML(const QString filePath, GOPathSetSetSet path)
{
    this->_error = "";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        this->_error = QObject::tr("Can't open file ") + filePath;
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" + file.fileName() + "</title>" << endl;
    out << "<meta charset = UTF-8>" << endl;
    out << "<style>body{width:100%}table,td{margin:0 auto;border:1px solid #CCC;border-collapse:collapse;font:small/1.5 'Tahoma','Bitstream Vera Sans',Verdana,Helvetica,sans-serif;}table{border:none;border:1px solid #CCC;}thead th,tbody th{color:#666;padding:5px 10px;border-left:1px solid #CCC;}tbody th{background:#fafafb;border-top:1px solid #CCC;text-align:left;}tbody tr td{padding:5px 10px;color:#666;}tbody tr:hover td{color:#454545;}tfoot td,tfoot th{border-left:none;border-top:1px solid #CCC;padding:4px;color:#666;}caption{text-align:left;font-size:120%;padding:10px 0;color:#666;}table a:link{color:#666;}table a:visited{color:#666;}table a:hover{color:#003366;text-decoration:none;}table a:active{color:#003366;}</style>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<input type = hidden value = ZHG/>";
    path.sort();
    if (path.list().size() == 0)
    {
        out << QObject::tr("Path or cut is not exist. ") << endl;
    }
    else
    {
        for (int i = 0; i < path.list().size(); ++i)
        {
            out << QObject::tr("<h2>Operator: %1 Output: %2 Index: %3</h2>").arg(path.endList().at(i).op->id()).arg(path.endList().at(i).outputIndex + 1).arg(path.endList().at(i).vectorIndex + 1) <<endl;
            out << "<table>" << endl;
            out << "<tr>" << endl;
            out << "<th>" + QObject::tr("No.") + "</th>" << endl;
            out << "<th>" + QObject::tr("Order") + "</th>" << endl;
            out << "<th>" + QObject::tr("ID List") + "</th>" << endl;
            out << "<th>" + QObject::tr("Name") + "</th>" << endl;
            if (path.list().at(i)->list().size() > 0)
            {
                out << "<th>" + path.list().at(i)->list().at(0)->getProbabilityName() + "</th>" << endl;
            }
            else
            {
                out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
            }
            out << "<th>" + QObject::tr("Importance") + "</th>" << endl;
            out << "</tr>" << endl;
            for (int j = 0; j < path.list().at(i)->list().size(); ++j)
            {
                out << "<tr>" << endl;
                out << "<td>" + QString("%1").arg(j + 1) + "</td>" << endl;
                out << "<td>" + QString("%1").arg(path.list().at(i)->list().at(j)->order()) + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toIdString() + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toNameString() + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toMarkovProbabilityString() + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toMarkovImportanceString() + "</td>" << endl;
                out << "</tr>" << endl;
            }
            out << "</table>" << endl;
        }
    }
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}
