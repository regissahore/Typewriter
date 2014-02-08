#include <cstdio>
#include <algorithm>
#include <QString>
#include <QObject>
#include <QFile>
#include <QMap>
#include <QTime>
#include <QTextStream>
#include <qmath.h>
#include "GoStatus.h"
#include "GoAccumulative.h"
#include "GoMarkovGraph.h"
#include "GoMarkovAnalysis.h"
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"
#include "GoMarkovChartData.h"
#include "GoMarkovOperatorFactory.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoSignal.h"
#include "GoMarkovCommonCause.h"
#include "MessageFactory.h"
#include "Messager.h"
#include "GoCutSet.h"
#include "GoPathSet.h"
#include "GoPathSetSet.h"
#include "GoPathSetSetSet.h"
#include "GoMarkovOperator12a.h"
using namespace std;

GoMarkovGraph::GoMarkovGraph() : GoGraph()
{
    delete this->_analysis;
    this->_analysis = new GoMarkovAnalysis();
}

GoMarkovGraph::~GoMarkovGraph()
{
    this->GoGraph::~GoGraph();
    this->_equivalent.clear();
}

QVector<GoMarkovEquivalent*> GoMarkovGraph::getEquivalent() const
{
    return this->_equivalent;
}

void GoMarkovGraph::addEquivalent(GoMarkovEquivalent *equivalent)
{
    this->_equivalent.push_back(equivalent);
}

QVector<GoMarkovCommonCause*> GoMarkovGraph::getCommonCause() const
{
    return this->_commonCause;
}

void GoMarkovGraph::addCommonCause(GoMarkovCommonCause *commonCause)
{
    this->_commonCause.push_back(commonCause);
}

void GoMarkovGraph::calcAccumulativeProbability(double time)
{
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        this->_messages.append(MessageRecord(QObject::tr("Error: Graph ") + this->_error, MessageFactory::TYPE_OUTPUT_ERROR));
        return;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        this->_operatorProcess = i;
        this->_currentOperatorName = GoMarkovOperatorFactory::typeName(((GoMarkovOperator*)list[i])->TypedItem::type()) + QString("-%1").arg(((GoMarkovOperator*)list[i])->id());
        if (list[i]->TypedItem::type() == GoMarkovOperatorFactory::Operator_Type_12A)
        {
            GoMarkovOperator12A *op = (GoMarkovOperator12A*)list[i];
            if (op->isUseDelta())
            {
                QVector<GoMarkovStatus> prevStatus;
                for (int i = 0; i < op->deltaNum(); ++i)
                {
                    GoMarkovStatus status = this->calcAccumulativeProbability(time, op->ids()->at(i), op->delta()->at(i), op);
                    prevStatus.push_back(status);
                }
                GoMarkovStatus status = this->calcAccumulativeProbability(time, "null", 1.0, op);
                prevStatus.push_front(status);
                op->calcOutputMarkovStatus(prevStatus, time);
            }
            else
            {
                op->calcOutputMarkovStatus(time);
            }
        }
        else
        {
            QVector<GoGraph::Output> commonList;
            if (GoMarkovOperatorFactory::isCommonPossible(list[i]->TypedItem::type()))
            {
                commonList = this->getCommonSignalList(list[i]);
            }
            if (commonList.size() == 0)
            {
                ((GoMarkovOperator*)list[i])->calcOutputMarkovStatus(time);
            }
            else
            {
                QVector<GoOperator*> commonOperator;
                QVector<int> commonIndex;
                for (int j = 0; j < commonList.size(); ++j)
                {
                    commonOperator.push_back(commonList[j].op);
                    commonIndex.push_back(commonList[j].outputIndex);
                }
                ((GoMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GoMarkovOperator*)list[i], commonOperator, commonIndex, time);
            }
        }
    }
    list.clear();
}

QSharedPointer<GoMarkovChartData> GoMarkovGraph::calcAccumulativeProbability(double totalTime, int count)
{
    QTime time;
    time.start();
    this->_messages.clear();
    this->_messages.append(MessageRecord("", MessageFactory::TYPE_OUTPUT_CLEAR));
    bool isOperatorError = false;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        GoMarkovOperator *op = (GoMarkovOperator*)this->_operator[i];
        if (op->errorDetect())
        {
            isOperatorError = true;
            this->_messages.append(MessageRecord(op->error(), MessageFactory::TYPE_OUTPUT_ERROR));
        }
        op->initCalculation(totalTime / (count - 1));
    }
    for (int i = 0; i < this->_commonCause.size(); ++i)
    {
        GoMarkovCommonCause *common = (GoMarkovCommonCause*)this->_commonCause[i];
        if (common->errorDetect())
        {
            isOperatorError = true;
            this->_messages.append(MessageRecord(common->error(), MessageFactory::TYPE_OUTPUT_ERROR));
        }
    }
    if (isOperatorError)
    {
        return QSharedPointer<GoMarkovChartData>();
    }

    this->_timeProcess = 0;
    this->_operatorProcess = 0;

    QVector<GoMarkovOperator*> sortedOperatorList;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        sortedOperatorList.push_back((GoMarkovOperator*)this->_operator.at(i));
    }
    for (int i = 0; i < sortedOperatorList.size(); ++i)
    {
        for (int j = i + 1; j < sortedOperatorList.size(); ++j)
        {
            bool isBigger = false;
            if (sortedOperatorList[i]->isGlobalFeedback() == sortedOperatorList[j]->isGlobalFeedback())
            {
                isBigger = sortedOperatorList[i]->id() > sortedOperatorList[j]->id();
            }
            else
            {
                isBigger = sortedOperatorList[i]->isGlobalFeedback() > sortedOperatorList[j]->isGlobalFeedback();
            }
            if (isBigger)
            {
                GoMarkovOperator *temp = sortedOperatorList[i];
                sortedOperatorList[i] = sortedOperatorList[j];
                sortedOperatorList[j] = temp;
            }
        }
    }

    QSharedPointer<GoMarkovChartData> data(new GoMarkovChartData());
    for (int i = 0; i < sortedOperatorList.size(); ++i)
    {
        GoMarkovOperator *op = (GoMarkovOperator*)sortedOperatorList[i];
        int outputNum = op->output()->number();
        if (outputNum == 1)
        {
            if (op->isGlobalFeedback())
            {
                if (op->type() != GoMarkovOperatorFactory::Operator_Type_Split)
                {
                    data->names.push_back(QObject::tr("\\'PR%1").arg(op->id()));
                }
                else
                {
                    data->names.push_back(QObject::tr("\\'PR%1").arg(op->getPrevOperator(0)->id()));
                }
            }
            else
            {
                if (op->type() != GoMarkovOperatorFactory::Operator_Type_Split)
                {
                    data->names.push_back(QObject::tr("PR%1").arg(op->id()));
                }
                else
                {
                    data->names.push_back(QObject::tr("PR%1").arg(op->getPrevOperator(0)->id()));
                }
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
                    if (op->type() != GoMarkovOperatorFactory::Operator_Type_Split)
                    {
                        data->names.push_back(QObject::tr("\\'PR%1(%2)").arg(op->id()).arg(j + 1));
                    }
                    else
                    {
                        data->names.push_back(QObject::tr("\\'PR%1(%2)").arg(op->getPrevOperator(0)->id()).arg(j + 1));
                    }
                }
                else
                {
                    if (op->type() != GoMarkovOperatorFactory::Operator_Type_Split)
                    {
                        data->names.push_back(QObject::tr("PR%1(%2)").arg(op->id()).arg(j + 1));
                    }
                    else
                    {
                        data->names.push_back(QObject::tr("PR%1(%2)").arg(op->getPrevOperator(0)->id()).arg(j + 1));
                    }
                }
                data->probabilities.push_back(QVector<DoubleVector>());
                data->lambdas.push_back(QVector<DoubleVector>());
                data->mus.push_back(QVector<DoubleVector>());
            }
        }
    }

    QVector<GoOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        GoMarkovOperator *op = (GoMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
    }
    for (int i = 0; i < count; ++i)
    {
        this->_timeProcess = i;
        double time = i * totalTime / (count - 1);
        data->times.push_back(time);

        for (int j = 0; j < list.size(); ++j)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[j];
            op->initMarkovStatus(time);
            op->prepareNextCalculation(i, time);
        }
        QVector<DoubleVector> lamdas;
        for (int j = 0; j < list.size(); ++j)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[j];
            lamdas.push_back(op->markovStatus()->frequencyBreakdown());
        }

        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GoMarkovOperator *op = this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(this->_commonCause[j]->breakdownIndividual());
                op->initWithCurrentLambda(time);
            }
        }
        this->calcAccumulativeProbability(time);
        if (this->getErrorMessage() != "")
        {
            return QSharedPointer<GoMarkovChartData>();
        }
        for (int j = 0, index = 0; j < sortedOperatorList.size(); ++j)
        {
            GoMarkovOperator* op = (GoMarkovOperator*)sortedOperatorList[j];
            int outputNum = op->markovOutputStatus()->size();
            for (int k = 0; k < outputNum; ++k)
            {
                data->probabilities[index].push_back(op->markovOutputStatus()->at(k)->probabilityNormal());
                data->lambdas[index].push_back(op->markovOutputStatus()->at(k)->frequencyBreakdown());
                data->mus[index++].push_back(op->markovOutputStatus()->at(k)->frequencyRepair());
            }
        }

        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            QVector<DoubleVector> r00;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GoMarkovOperator *op = (GoMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityBreakdown(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < sortedOperatorList.size(); ++k)
            {
                GoMarkovOperator* op = (GoMarkovOperator*)sortedOperatorList[k];
                int outputNum = op->markovOutputStatus()->size();
                for (int l = 0; l < outputNum; ++l)
                {
                    r00.push_back(op->markovOutputStatus()->at(l)->probabilityNormal());
                }
            }

            QVector<DoubleVector> r11;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GoMarkovOperator *op = (GoMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityNormal(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < sortedOperatorList.size(); ++k)
            {
                GoMarkovOperator* op = (GoMarkovOperator*)sortedOperatorList[k];
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

        for (int j = 0; j < list.size(); ++j)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[j];
            op->markovStatus()->setFrequencyBreakdown(lamdas[j]);
            op->finishCalculation();
        }
    }

    this->_messages.append(MessageRecord(QObject::tr("Analysis Completed. It takes %1 seconds.").arg(time.elapsed() / 1000.0), MessageFactory::TYPE_OUTPUT_CORRECT));
    return data;
}

GoMarkovStatus GoMarkovGraph::calcAccumulativeProbability(double time, QString id, double delta, GoMarkovOperator* stopOperator)
{
    QVector<GoOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i] == stopOperator)
        {
            GoMarkovStatus *status = stopOperator->getPrevMarkovStatus();
            GoMarkovStatus res;
            res.setProbabilityNormal(status->probabilityNormal());
            res.setFrequencyBreakdown(status->frequencyBreakdown());
            res.setFrequencyRepair(status->frequencyRepair());
            return res;
        }
        if (list[i]->TypedItem::type() == GoMarkovOperatorFactory::Operator_Type_12A)
        {
            GoMarkovOperator12A *op = (GoMarkovOperator12A*)list[i];
            if (op->isUseDelta())
            {
                QVector<GoMarkovStatus> prevStatus;
                for (int i = 0; i < op->deltaNum(); ++i)
                {
                    GoMarkovStatus status = this->calcAccumulativeProbability(time, op->ids()->at(i), op->delta()->at(i), op);
                    prevStatus.push_back(status);
                }
                GoMarkovStatus status = this->calcAccumulativeProbability(time, "null", 1.0, op);
                prevStatus.push_front(status);
                op->calcOutputMarkovStatus(prevStatus, time);
            }
            else
            {
                op->calcOutputMarkovStatus(time);
            }
        }
        else
        {
            QVector<GoGraph::Output> commonList;
            if (GoMarkovOperatorFactory::isCommonPossible(list[i]->TypedItem::type()))
            {
                commonList = this->getCommonSignalList(list[i]);
            }
            if (commonList.size() == 0)
            {
                ((GoMarkovOperator*)list[i])->calcOutputMarkovStatus(time);
            }
            else
            {
                QVector<GoOperator*> commonOperator;
                QVector<int> commonIndex;
                for (int j = 0; j < commonList.size(); ++j)
                {
                    commonOperator.push_back(commonList[j].op);
                    commonIndex.push_back(commonList[j].outputIndex);
                }
                ((GoMarkovAnalysis*)this->_analysis)->calcMarkovStatus((GoMarkovOperator*)list[i], commonOperator, commonIndex, time);
            }
            if (QString("%1").arg(list[i]->id()) == id)
            {
                GoMarkovOperator *op = (GoMarkovOperator*)list[i];
                for (int i = 0; i < list[i]->output()->number(); ++i)
                {
                    op->markovOutputStatus()->at(i)->setProbabilityNormal(op->markovOutputStatus()->at(i)->probabilityBreakdown() * delta);
                    op->markovOutputStatus()->at(i)->setFrequencyBreakdown(op->markovOutputStatus()->at(i)->frequencyBreakdown() * delta);
                    op->markovOutputStatus()->at(i)->setFrequencyRepair(op->markovOutputStatus()->at(i)->frequencyRepair() * delta);
                }
            }
        }
    }
    list.clear();
    GoMarkovStatus res;
    return res;
}

bool GoMarkovGraph::isContainCycleDfs(QVector<bool> &visit,
                                QVector<int> &dfn,
                                QVector<int> &low,
                                QVector<int> &stack,
                                int &timeStamp,
                                int u)
{
    dfn[u] = low[u] = timeStamp++;
    visit[u] = true;
    stack.push_back(u);
    GoOperator *op = this->_operator[u];
    if (op->TypedItem::type() != GoMarkovOperatorFactory::Operator_Type_21)
    {
        for (int i = 0; i < op->output()->number(); ++i)
        {
            for (int j = 0; j < op->output()->signal()->at(i)->size(); ++j)
            {
                GoOperator *next = op->output()->signal()->at(i)->at(j)->next(op);
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

QVector< QVector<GoGraph::Output> > GoMarkovGraph::getAncestorList(GoOperator *op, int outputIndex, int signalIndex)
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
        GoSignal *signal = op->input()->signal()->at(i);
        GoOperator *prev = signal->next(op);
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
        if (prev->TypedItem::type() != GoMarkovOperatorFactory::Operator_Type_21)
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
        GoSignal *signal = op->subInput()->signal()->at(i);
        GoOperator *prev = signal->next(op);
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
        if (prev->TypedItem::type() != GoMarkovOperatorFactory::Operator_Type_21)
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

GoPathSetSetSet GoMarkovGraph::findPath(int order)
{
    GoPathSetSetSet path;
    this->calcAccumulativeProbability(1e10, 2);
    if (this->_error != "")
    {
        return path;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<DoubleVector>* > normals;
    for (int i = 0; i < list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)list[i];
        QVector<DoubleVector> *normal = new QVector<DoubleVector>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            normal->push_back(op->markovOutputStatus()->at(i)->probabilityNormal());
        }
        normals[op->realID()] = normal;
    }
    GoPathSet tempPath;
    if (order > list.size())
    {
        order = list.size();
    }
    for (int i = 0; i < list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
        op->initQualitativeOutput();
        op->setQualitativeStatus(0.0);
    }
    for (int i = 1; i <= order; ++i)
    {
        this->findPathDfs(normals, path, list, tempPath, 0, 0, i);
    }
    for (auto it = normals.begin(); it != normals.end(); ++it)
    {
        delete it.value();
    }
    normals.clear();
    return path;
}

GoPathSetSetSet GoMarkovGraph::findCut(int order)
{
    GoPathSetSetSet path;
    this->calcAccumulativeProbability(1e10, 2);
    if (this->_error != "")
    {
        return path;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<DoubleVector>* > fails;
    for (int i = 0; i < list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)list[i];
        QVector<DoubleVector> *fail = new QVector<DoubleVector>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            fail->push_back(op->markovOutputStatus()->at(i)->probabilityBreakdown());
        }
        fails[op->realID()] = fail;
    }
    GoCutSet tempPath;
    if (order > list.size())
    {
        order = list.size();
    }
    for (int i = 0; i < list.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)list[i];
        op->initOutputMarkovStatus();
        op->initQualitativeOutput();
        op->setQualitativeStatus(1.0);
    }
    for (int i = 1; i <= order; ++i)
    {
        this->findCutDfs(fails, path, list, tempPath, 0, 0, i);
    }
    for (auto it = fails.begin(); it != fails.end(); ++it)
    {
        delete it.value();
    }
    fails.clear();
    return path;
}

void GoMarkovGraph::findPathDfs(QMap<int, QVector<DoubleVector> *> &normals, GoPathSetSetSet &path, QVector<GoOperator*> &list, GoPathSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        for (int i = 0; i < list.size(); ++i)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[i];
            op->calcQualitativeProbability();
        }
        QVector<GoPathSetSetSet::End> ends;
        QVector<double> probabilityList;
        for (int i = 0; i < list.size(); ++i)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[i];
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (op->output()->signal()->at(j)->size() == 0)
                {
                    for (int k = 0; k < op->qualitativeOutput()->at(j).length(); ++k)
                    {
                        if (op->qualitativeOutput()->at(j).getValue(k) > 0.5)
                        {
                            GoPathSetSetSet::End end;
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
    if (!((GoMarkovOperator*)list[index])->isGlobalFeedback())
    {
        if (!GoMarkovOperatorFactory::isLogical(list[index]->type()))
        {
            GoMarkovOperator* op = (GoMarkovOperator*)list[index];
            op->setQualitativeStatus(1.0);
            tempPath.add(list[index]);
            this->findPathDfs(normals, path, list, tempPath, index + 1, number + 1, order);
            op->setQualitativeStatus(0.0);
            tempPath.removeEnd();
        }
    }
    this->findPathDfs(normals, path, list, tempPath, index + 1, number, order);
}

void GoMarkovGraph::findCutDfs(QMap<int, QVector<DoubleVector> *> &fails, GoPathSetSetSet &cut, QVector<GoOperator*> &list, GoCutSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        for (int i = 0; i < list.size(); ++i)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[i];
            op->calcQualitativeProbability();
        }
        QVector<GoPathSetSetSet::End> ends;
        QVector<double> probabilityList;
        for (int i = 0; i < list.size(); ++i)
        {
            GoMarkovOperator *op = (GoMarkovOperator*)list[i];
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (op->output()->signal()->at(j)->size() == 0)
                {
                    for (int k = 0; k < op->qualitativeOutput()->at(j).length(); ++k)
                    {
                        if (op->qualitativeOutput()->at(j).getValue(k) < 0.5)
                        {
                            GoPathSetSetSet::End end;
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
    if (!((GoMarkovOperator*)list[index])->isGlobalFeedback())
    {
        if (!GoMarkovOperatorFactory::isLogical(list[index]->type()))
        {
            GoMarkovOperator* op = (GoMarkovOperator*)list[index];
            op->setQualitativeStatus(0.0);
            tempPath.add(list[index]);
            this->findCutDfs(fails, cut, list, tempPath, index + 1, number + 1, order);
            op->setQualitativeStatus(1.0);
            tempPath.removeEnd();
        }
    }
    this->findCutDfs(fails, cut, list, tempPath, index + 1, number, order);
}

int GoMarkovGraph::timeProcess() const
{
    return this->_timeProcess;
}

int GoMarkovGraph::operatorProcess() const
{
    return this->_operatorProcess;
}

int GoMarkovGraph::totalOperatorNum() const
{
    return this->_operator.size();
}

QString GoMarkovGraph::currentOperatorName() const
{
    return this->_currentOperatorName;
}

void GoMarkovGraph::printQualitativeOutput() const
{
    FILE *file = fopen("qualitative.log", "a");
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        GoMarkovOperator* op = (GoMarkovOperator*)this->_operator[i];
        fprintf(file, "%d-%d %d: ", op->id(), op->type(), op->realID());
        if (GoMarkovOperatorFactory::isLogical(op->type()))
        {
            fprintf(file, "LOGIC ");
        }
        else
        {
            fprintf(file, "%lf ", op->qualitativeStatus().getValue(0));
        }
        for (int j = 0; j < op->output()->number(); ++j)
        {
            fprintf(file, "%lf\n", op->qualitativeOutput()->at(j).getValue(0));
        }
    }
    for (int i = 0; i < 80; ++i)
    {
        fprintf(file, "=");
    }
    fprintf(file, "\n");
    fclose(file);
}

bool GoMarkovGraph::saveAsHTML(const QString filePath, GoPathSetSetSet path)
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
