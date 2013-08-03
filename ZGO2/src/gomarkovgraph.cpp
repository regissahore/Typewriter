#include <cstdio>
#include <QString>
#include <QObject>
#include <QFile>
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
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[i];
        op->initOutputMarkovStatus();
        int outputNum = op->markovOutputStatus()->size();
        if (outputNum == 1)
        {
            data->names.push_back(QString("%1").arg(this->_operator[i]->id()));
            data->probabilities.push_back(QVector<double>());
            data->lambdas.push_back(QVector<double>());
            data->mius.push_back(QVector<double>());
        }
        else
        {
            for (int j = 0; j < outputNum; ++j)
            {
                data->names.push_back(QString("%1 (%2)").arg(this->_operator[i]->id()).arg(j + 1));
                data->probabilities.push_back(QVector<double>());
                data->lambdas.push_back(QVector<double>());
                data->mius.push_back(QVector<double>());
            }
        }
    }
    for (int i = 0; i < count; ++i)
    {
        // Record initial value of lamda.
        QVector<double> lamdas;
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            lamdas.push_back(op->markovStatus()->frequencyBreakdown());
        }
        // Calculate without common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setFrequencyBreakdown(op->markovStatus()->frequencyBreakdown() + this->_commonCause[j]->breakdownCommon());
            }
        }
        double time = i * totalTime / (count - 1);
        data->times.push_back(time);
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            double c12 = 0.0;
            for (int k = 0; k < this->_commonCause.size(); ++k)
            {
                if (this->_commonCause[k]->containOperator(op))
                {
                    c12 = this->_commonCause[k]->calcCommonCause(time);
                    break;
                }
            }
            op->initMarkovStatus(time, c12);
        }
        this->calcAccumulativeProbability(time);
        if (this->getErrorMessage() != "")
        {
            delete data;
            return 0L;
        }
        for (int j = 0, index = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[j];
            int outputNum = op->markovOutputStatus()->size();
            for (int k = 0; k < outputNum; ++k)
            {
                data->probabilities[index].push_back(op->markovOutputStatus()->at(k)->probabilityNormal());
                data->lambdas[index].push_back(op->markovOutputStatus()->at(k)->frequencyBreakdown());
                data->mius[index++].push_back(op->markovOutputStatus()->at(k)->frequencyRepair());
            }
        }
        // Fixed the error caused by common cause.
        for (int j = 0; j < this->_commonCause.size(); ++j)
        {
            QVector<double> r00;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityBreakdown(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[k];
                for (int l = 0; l < this->_operator[k]->output()->number(); ++l)
                {
                    r00.push_back(op->markovOutputStatus()->at(l)->probabilityNormal());
                }
            }

            QVector<double> r11;
            for (int k = 0; k < this->_commonCause[j]->operators()->size(); ++k)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)this->_commonCause[j]->operators()->at(k);
                op->markovStatus()->setProbabilityNormal(1.0);
            }
            this->calcAccumulativeProbability(time);
            for (int k = 0; k < this->_operator.size(); ++k)
            {
                GOMarkovOperator* op = (GOMarkovOperator*)this->_operator[k];
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
        for (int j = 0; j < this->_operator.size(); ++j)
        {
            GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[j];
            op->markovStatus()->setFrequencyBreakdown(lamdas[j]);
        }
    }
    message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_CORRECT);
    message->paramString = QString("Analysis Completed. It takes %1 seconds. ").arg(time.elapsed() / 1000.0);
    this->sendMessage(message);
    return data;
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

QVector<GOOperator*> GOMarkovGraph::getTopologicalOrder()
{
    QVector<GOOperator*> topList;
    QVector<bool> outside;
    QVector<int> inputNumber;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        outside.push_back(false);
        int carry = 0;
        GOMarkovOperator *op = (GOMarkovOperator*)this->_operator[i];
        for (int j = 0; j < op->input()->number(); ++j)
        {
            if (op->getPrevOperator(j)->TypedItem::type() == GOMarkovOperatorFactory::Operator_Type_21)
            {
                ++carry;
            }
        }
        for (int j = 0; j < op->subInput()->number(); ++j)
        {
            if (op->getPrevSubOperator(j)->TypedItem::type() == GOMarkovOperatorFactory::Operator_Type_21)
            {
                ++carry;
            }
        }
        inputNumber.push_back(this->_operator[i]->input()->number() + this->_operator[i]->subInput()->number() - carry);
    }
    while (topList.size() != this->_operator.size())
    {
        for (int i = 0; i < this->_operator.size(); ++i)
        {
            if (inputNumber[i] == 0 && !outside[i])
            {
                topList.push_back(this->_operator[i]);
                outside[i] = true;
                for (int j = 0; j < this->_operator[i]->output()->number(); ++j)
                {
                    for (int k = 0; k < this->_operator[i]->output()->signal()->at(j)->size(); ++k)
                    {
                        GOOperator *next = this->_operator[i]->output()->signal()->at(j)->at(k)->next(this->_operator[i]);
                        bool appear = false;
                        for (int l = 0; l < k; ++l)
                        {
                            GOOperator *history = this->_operator[i]->output()->signal()->at(j)->at(l)->next(this->_operator[i]);
                            if (next == history)
                            {
                                appear = true;
                                break;
                            }
                        }
                        if (appear)
                        {
                            continue;
                        }
                        int index = this->_operatorPos[next];
                        --inputNumber[index];
                    }
                }
            }
        }
    }
    return topList;
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
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        return path;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
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
        this->findPathDfs(path, list, tempPath, 0, 0, i);
    }
    return path;
}

GOPathSetSetSet GOMarkovGraph::findCut(int order)
{
    GOPathSetSetSet path;
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        return path;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
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
        this->findCutDfs(path, list, tempPath, 0, 0, i);
    }
    return path;
}

void GOMarkovGraph::findPathDfs(GOPathSetSetSet &path, QVector<GOOperator*> &list, GOPathSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        QVector<GOOperator*> endList;
        for (int i = 0; i < list.size(); ++i)
        {
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (list[i]->output()->signal()->at(j)->size() == 0)
                {
                    endList.push_back(list[i]);
                    break;
                }
            }
        }
        bool flag = false;
        if (endList.size() > path.endList().size())
        {
            flag = true;
        }
        else
        {
            for (int i = 0; i < path.list().size(); ++i)
            {
                bool contain = false;
                for (int j = 0; j < path.list().at(i)->list().size(); ++j)
                {
                    if (tempPath.isContain(path.list().at(i)->list().at(j)))
                    {
                        contain = true;
                        break;
                    }
                }
                if (!contain)
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
        {
            for (int i = 0; i < list.size(); ++i)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)list[i];
                op->calcOutputMarkovStatus(0.0);
            }
            for (int i = 0; i < endList.size(); ++i)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)endList[i];
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    if (op->markovOutputStatus()->at(j)->probabilityNormal() >= 1.0 - 1e-8)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                {
                    path.add(endList[i], tempPath.copy());
                }
            }
        }
        return;
    }
    if (number > order || index >= list.size())
    {
        return;
    }
    if (!GOMarkovOperatorFactory::isLogical(list[index]->type()))
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[index];
        op->markovStatus()->setProbabilityNormal(1.0);
        tempPath.add(list[index]);
        this->findPathDfs(path, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
    }
    GOMarkovOperator* op = (GOMarkovOperator*)list[index];
    op->markovStatus()->setProbabilityNormal(0.0);
    this->findPathDfs(path, list, tempPath, index + 1, number, order);
}

void GOMarkovGraph::findCutDfs(GOPathSetSetSet &cut, QVector<GOOperator*> &list, GOCutSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        QVector<GOOperator*> endList;
        for (int i = 0; i < list.size(); ++i)
        {
            for (int j = 0; j < list[i]->output()->number(); ++j)
            {
                if (list[i]->output()->signal()->at(j)->size() == 0)
                {
                    endList.push_back(list[i]);
                    break;
                }
            }
        }
        bool flag = false;
        if (endList.size() > cut.endList().size())
        {
            flag = true;
        }
        else
        {
            for (int i = 0; i < cut.list().size(); ++i)
            {
                bool contain = false;
                for (int j = 0; j < cut.list().at(i)->list().size(); ++j)
                {
                    if (tempPath.isContain(cut.list().at(i)->list().at(j)))
                    {
                        contain = true;
                        break;
                    }
                }
                if (!contain)
                {
                    flag = true;
                    break;
                }
            }
        }
        if (flag)
        {
            for (int i = 0; i < list.size(); ++i)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)list[i];
                op->calcOutputMarkovStatus(0.0);
            }
            for (int i = 0; i < endList.size(); ++i)
            {
                GOMarkovOperator *op = (GOMarkovOperator*)endList[i];
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    if (op->markovOutputStatus()->at(j)->probabilityBreakdown() >= 1.0 - 1e-8)
                    {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                {
                    cut.add(endList[i], tempPath.copy());
                }
            }
        }
        return;
    }
    if (number > order || index >= list.size())
    {
        return;
    }
    if (!GOMarkovOperatorFactory::isLogical(list[index]->type()))
    {
        GOMarkovOperator* op = (GOMarkovOperator*)list[index];
        op->markovStatus()->setProbabilityBreakdown(1.0);
        tempPath.add(list[index]);
        this->findCutDfs(cut, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
    }
    GOMarkovOperator* op = (GOMarkovOperator*)list[index];
    op->markovStatus()->setProbabilityBreakdown(0.0);
    this->findCutDfs(cut, list, tempPath, index + 1, number, order);
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
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyBreakdown() << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovStatus()->frequencyRepair() << "</td>";
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
        out << QString("<td>Normal</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityNormal()) << endl;
        out << QString("<td>Breakdown</td><td>%1</td>").arg(((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->probabilityBreakdown()) << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Failure Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown() << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyBreakdown()) << "</td>";
        out << "</tr>" << endl;
        out << "<tr>" << endl;
        out << "<td>" + QObject::tr("Repair Rate") + "</td>" << endl;
        out << "<td>" << ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair() << "</td>";
        out << "<td>" << (1.0 / ((GOMarkovOperator*)list[i])->markovOutputStatus()->at(0)->frequencyRepair()) << "</td>";
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
