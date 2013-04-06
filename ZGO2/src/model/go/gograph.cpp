#include <QObject>
#include <QFile>
#include <QTextStream>
#include "gograph.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "goanalysis.h"
#include "gooperatorfactory.h"
#include "gostatus.h"
#include "goaccumulative.h"
#include "gocutset.h"
#include "gopathset.h"
#include "gopathsetset.h"
#include "gopathsetsetset.h"

GOGraph::GOGraph()
{
    this->_error = "";
}

GOGraph::~GOGraph()
{
    this->_source.clear();
    this->_operator.clear();
    this->_signal.clear();
    this->_operatorPos.clear();
}

QVector<int> GOGraph::getSource() const
{
    return this->_source;
}

QVector<GOOperator*> GOGraph::getOperator() const
{
    return this->_operator;
}

QVector<GOSignal*> GOGraph::getSignal() const
{
    return this->_signal;
}

void GOGraph::addOperator(GOOperator *op)
{
    if (op->type() == GOOperatorFactory::Operator_Type_4 ||
            op->type() == GOOperatorFactory::Operator_Type_5)
    {
        this->_source.push_back(this->_operator.size());
    }
    this->_operatorPos[op] = this->_operator.size();
    this->_operator.push_back(op);
}

void GOGraph::addSignal(GOSignal *signal)
{
    this->_signal.push_back(signal);
}

QString GOGraph::getErrorMessage() const
{
    return this->_error;
}

/**
 * Calculate the accumulative probability.
 */
void GOGraph::calcAccumulativeProbability()
{
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        return;
    }
    QVector<GOOperator*> list = this->getTopologicalOrder();
    GOAnalysis *analysis = new GOAnalysis();
    for (int i = 0; i < list.size(); ++i)
    {
        QVector<GOGraph::Output> commonList;
        if (list[i]->input()->number() + list[i]->subInput()->number() > 1)
        {
            commonList = this->getCommonSignalList(list[i]);
        }
        if (commonList.size() == 0)
        {
            analysis->calcAccumulativeProbability(list[i]);
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
            analysis->calcAccumulativeProbability(list[i], commonOperator, commonIndex);
        }
    }
    delete analysis;
    list.clear();
}

/**
 * Check if the graph contains cycle.
 * Check if the graph is connected.
 * @return Returns true if the graph does not contain error, otherwise false.
 */
bool GOGraph::checkCycleAndConnection()
{
    QVector<bool> visit;
    QVector<int> dfn;
    QVector<int> low;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        visit.push_back(false);
        dfn.push_back(-1);
        low.push_back(-1);
    }
    int timeStamp = 0;
    QVector<int> stack;
    for (int i = 0; i < this->_source.size(); ++i)
    {
        int u = this->_source[i];
        if (dfn[u] == -1)
        {
            if (this->isContainCycleDfs(visit, dfn, low, stack, timeStamp, u))
            {
                this->_error = QObject::tr("The GO graph contains cycle. ");
                return false;
            }
        }
    }
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        if (dfn[i] == -1)
        {
            this->_error = QObject::tr("The GO graph is not connected. ");
            return false;
        }
    }
    return true;
}

bool GOGraph::isContainCycleDfs(QVector<bool> &visit,
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

/**
 * Get the topological order for analysis order.
 * @return The topological order.
 */
QVector<GOOperator*> GOGraph::getTopologicalOrder()
{
    QVector<GOOperator*> topList;
    QVector<bool> outside;
    QVector<int> inputNumber;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        outside.push_back(false);
        inputNumber.push_back(this->_operator[i]->input()->number() + this->_operator[i]->subInput()->number());
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
                        int index = this->_operatorPos[next];
                        --inputNumber[index];
                    }
                }
            }
        }
    }
    return topList;
}

/**
 * Get the ancestor list, the parameter operator is in the frontest position.
 * @param op The operator.
 * @param index The index is the output index of the operator.
 * @return The vector of the path, which is a vector of struct CommonSignal.
 */
QVector< QVector<GOGraph::Output> > GOGraph::getAncestorList(GOOperator *op, int outputIndex, int signalIndex)
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
        QVector< QVector<Output> > pathList = this->getAncestorList(prev, outputIndex, signalIndex);
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
        QVector< QVector<Output> > pathList = this->getAncestorList(prev, outputIndex, signalIndex);
        for (int j = 0; j < pathList.size(); ++j)
        {
            pathList[j].push_front(commonSignal);
            vector.push_back(pathList[j]);
        }
    }
    return vector;
}

/**
 * Get all common signal list, which is actually a list of operators.
 * @param op
 * @return The vector of common signal.
 */
QVector<GOGraph::Output> GOGraph::getCommonSignalList(GOOperator *op)
{
    QVector< QVector<Output> > ancestorPath = this->getAncestorList(op, 0, 0);
    QVector<Output> commonList;
    for (int i = 0; i < ancestorPath.size(); ++i)
    {
        for (int j = i + 1; j < ancestorPath.size(); ++j)
        {
            bool findCommon = false;
            for (int ii = 1; ii < ancestorPath[i].size() && !findCommon; ++ii)
            {
                for (int jj = 1; jj < ancestorPath[j].size() && !findCommon; ++jj)
                {
                    if (ancestorPath[i][ii].op == ancestorPath[j][jj].op &&
                            ancestorPath[i][ii].outputIndex == ancestorPath[j][jj].outputIndex &&
                            ancestorPath[i][ii].signalIndex != ancestorPath[j][jj].signalIndex)
                    {
                        findCommon = true;
                        bool appeared = false;
                        for (int k = 0; k < commonList.size(); ++k)
                        {
                            if (ancestorPath[i][ii].op == commonList[k].op &&
                                    ancestorPath[i][ii].outputIndex == commonList[k].outputIndex)
                            {
                                appeared = true;
                                break;
                            }
                        }
                        if (!appeared)
                        {
                            commonList.push_back(ancestorPath[i][ii]);
                        }
                    }
                }
            }
        }
    }
    ancestorPath.clear();
    return commonList;
}

GOPathSetSetSet GOGraph::findPath(int order)
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
    for (int i = 1; i <= order; ++i)
    {
        this->findPathDfs(path, list, tempPath, 0, 0, i);
    }
    return path;
}

void GOGraph::findPathDfs(GOPathSetSetSet &path, QVector<GOOperator *> &list, GOPathSet &tempPath, int index, int number, int order)
{
    if (number > order || index >= list.size())
    {
        return;
    }
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
            this->calcAccumulativeProbability();
            for (int i = 0; i < endList.size(); ++i)
            {
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    if (endList[i]->accmulatives()->at(j)->accumulative(1) == BigDecimal::one())
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
    if (!GOOperatorFactory::isLogical(list[index]->type()))
    {
        GOStatus *copy = new GOStatus();
        copy->setNumber(list[index]->status()->number());
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            copy->setProbability(i, list[index]->status()->probability(i));
            list[index]->status()->setProbability(i, BigDecimal::zero());
        }
        list[index]->status()->setProbability(1, BigDecimal::one());
        tempPath.add(list[index]);
        this->findPathDfs(path, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            list[index]->status()->setProbability(i, copy->probability(i));
        }
        delete copy;
    }
    this->findPathDfs(path, list, tempPath, index + 1, number, order);
}

GOPathSetSetSet GOGraph::findCut(int order)
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
    for (int i = 1; i <= order; ++i)
    {
        this->findCutDfs(path, list, tempPath, 0, 0, i);
    }
    return path;
}

void GOGraph::findCutDfs(GOPathSetSetSet &cut, QVector<GOOperator *> &list, GOCutSet &tempPath, int index, int number, int order)
{
    if (number > order || index >= list.size())
    {
        return;
    }
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
            this->calcAccumulativeProbability();
            for (int i = 0; i < endList.size(); ++i)
            {
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    int number = endList[i]->accmulatives()->at(j)->number();
                    BigDecimal a = endList[i]->accmulatives()->at(j)->accumulative(number - 1);
                    BigDecimal b = endList[i]->accmulatives()->at(j)->accumulative(number - 2);
                    if (a - b == BigDecimal::one())
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
    if (!GOOperatorFactory::isLogical(list[index]->type()))
    {
        GOStatus *copy = new GOStatus();
        copy->setNumber(list[index]->status()->number());
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            copy->setProbability(i, list[index]->status()->probability(i));
            list[index]->status()->setProbability(i, BigDecimal::zero());
        }
        list[index]->status()->setProbability(list[index]->status()->number() - 1, BigDecimal::one());
        tempPath.add(list[index]);
        this->findCutDfs(cut, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            list[index]->status()->setProbability(i, copy->probability(i));
        }
        delete copy;
    }
    this->findCutDfs(cut, list, tempPath, index + 1, number, order);
}

/**
 * Save the result to a HTML file.
 * @param path The file path.
 * @return Returns true if succeed, otherwise false.
 */
bool GOGraph::saveAsHTML(const QString filePath)
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
            out << "<td>" << list[i]->status()->probability(j).toString() << "</td>";
            out << "</tr>" << endl;
        }
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "<td>" << endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("Status") + "</th>" << endl;
        out << "<th>" + QObject::tr("Accumulative") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j < list[i]->accmulatives()->at(0)->number(); ++j)
        {
            out << "<tr>" << endl;
            out << QString("<td style='text-align:center;'>%1</td>").arg(j);
            out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j).toString() << "</td>";
            if (j == 0)
            {
                out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j).toString() << "</td>";
            }
            else
            {
                out << "<td>" << (list[i]->accmulatives()->at(0)->accumulative(j) - list[i]->accmulatives()->at(0)->accumulative(j - 1)).toString() << "</td>";
            }
            out << "</tr>" << endl;
        }
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

bool GOGraph::saveAsHTML(const QString filePath, GOPathSetSetSet path)
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
    for (int i = 0; i < path.list().size(); ++i)
    {
        out << QString("<h2>%1</h2>").arg(path.endList().at(i)->id()) <<endl;
        out << "<table>" << endl;
        out << "<tr>" << endl;
        out << "<th>" + QObject::tr("No.") + "</th>" << endl;
        out << "<th>" + QObject::tr("Order") + "</th>" << endl;
        out << "<th>" + QObject::tr("ID List") + "</th>" << endl;
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j < path.list().at(i)->list().size(); ++j)
        {
            out << "<tr>" << endl;
            out << "<td>" + QString("%1").arg(j + 1) + "</td>" << endl;
            out << "<td>" + QString("%1").arg(path.list().at(i)->list().at(j)->order()) + "</td>" << endl;
            out << "<td>" + path.list().at(i)->list().at(j)->toIdString() + "</td>" << endl;
            out << "<td>" + path.list().at(i)->list().at(j)->toProbabilityString() + "</td>" << endl;
            out << "</tr>" << endl;
        }
        out << "</table>" << endl;
    }
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}
