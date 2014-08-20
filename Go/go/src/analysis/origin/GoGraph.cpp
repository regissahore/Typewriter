#include <QObject>
#include <QFile>
#include <QMap>
#include <QTextStream>
#include <cstdio>
#include "GoGraph.h"
#include "GoOperator.h"
#include "GoSignal.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoAnalysis.h"
#include "GoOperatorFactory.h"
#include "GoStatus.h"
#include "GoAccumulative.h"
#include "GoCutSet.h"
#include "GoPathSet.h"
#include "GoPathSetSet.h"
#include "GoPathSetSetSet.h"
#include "GoMarkovOperator.h"
#include "GoMarkovOperatorFactory.h"

GoGraph::GoGraph() : Messager()
{
    this->_error = "";
    this->_analysis = new GoAnalysis();
}

GoGraph::~GoGraph()
{
    this->_source.clear();
    this->_operator.clear();
    this->_operatorPos.clear();
    this->Messager::~Messager();
}

QVector<int> GoGraph::getSource() const
{
    return this->_source;
}

QVector<GoOperator*> GoGraph::getOperator() const
{
    return this->_operator;
}

void GoGraph::addOperator(GoOperator *op)
{
    if (op->type() == GoOperatorFactory::Operator_Type_4 ||
            op->type() == GoOperatorFactory::Operator_Type_5)
    {
        this->_source.push_back(this->_operator.size());
    }
    this->_operatorPos[op] = this->_operator.size();
    this->_operator.push_back(op);
}

QString GoGraph::getErrorMessage() const
{
    return this->_error;
}

QVector<GoGraph::MessageRecord> GoGraph::messages() const
{
    return this->_messages;
}

void GoGraph::calcAccumulativeProbability()
{
    this->_error = "";
    if (!this->checkCycleAndConnection())
    {
        return;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    for (int i = 0; i < list.size(); ++i)
    {
        QVector<GoGraph::Output> commonList;
        if (list[i]->input()->number() + list[i]->subInput()->number() > 1)
        {
            commonList = this->getCommonSignalList(list[i]);
        }
        if (commonList.size() == 0)
        {
            this->_analysis->calcAccumulativeProbability(list[i]);
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
            this->_analysis->calcAccumulativeProbability(list[i], commonOperator, commonIndex);
        }
    }
    list.clear();
}

bool GoGraph::checkCycleAndConnection()
{
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        for (int j = 0; j < this->_operator.at(i)->input()->number(); ++j)
        {
            if (this->_operator.at(i)->input()->signal()->at(j) == nullptr)
            {
                this->_error = QObject::tr("The input of the operator is null. ");
                return false;
            }
        }
        for (int j = 0; j < this->_operator.at(i)->subInput()->number(); ++j)
        {
            if (this->_operator.at(i)->subInput()->signal()->at(j) == nullptr)
            {
                this->_error = QObject::tr("The sub input of the operator is null. ");
                return false;
            }
        }
    }
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
                this->_error = QObject::tr("The Go graph contains cycle. ");
                return false;
            }
        }
    }
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        if (dfn[i] == -1 && this->_operator[i]->type() != GoMarkovOperatorFactory::Operator_Type_21)
        {
            this->_error = QObject::tr("The Go graph is not connected. ");
            return false;
        }
    }
    return true;
}

bool GoGraph::isContainCycleDfs(QVector<bool> &visit,
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

QVector<GoOperator*> GoGraph::getTopologicalOrder()
{
    QVector<GoOperator*> topList;
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
                        GoOperator *next = this->_operator[i]->output()->signal()->at(j)->at(k)->next(this->_operator[i]);
                        bool appear = false;
                        for (int l = 0; l < k; ++l)
                        {
                            GoOperator *history = this->_operator[i]->output()->signal()->at(j)->at(l)->next(this->_operator[i]);
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

QVector< QVector<GoGraph::Output> > GoGraph::getAncestorList(GoOperator *op, int outputIndex, int signalIndex)
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
        QVector< QVector<Output> > pathList = this->getAncestorList(prev, outputIndex, signalIndex);
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
        QVector< QVector<Output> > pathList = this->getAncestorList(prev, outputIndex, signalIndex);
        for (int j = 0; j < pathList.size(); ++j)
        {
            pathList[j].push_front(commonSignal);
            vector.push_back(pathList[j]);
        }
    }
    return vector;
}

QVector<GoGraph::Output> GoGraph::getCommonSignalList(GoOperator *op)
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

GoPathSetSetSet GoGraph::findPath(int order)
{
    GoPathSetSetSet path;
    this->calcAccumulativeProbability();
    if (this->_error != "")
    {
        return path;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<double>* > normals;
    for (int i = 0; i < list.size(); ++i)
    {
        GoOperator* op = list[i];
        QVector<double> *normal = new QVector<double>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            normal->push_back(op->accmulatives()->at(i)->probability(1));
        }
        normals[op->realID()] = normal;
    }
    GoPathSet tempPath;
    if (order > list.size())
    {
        order = list.size();
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

void GoGraph::findPathDfs(QMap<int, QVector<double> *> &normals, GoPathSetSetSet &path, QVector<GoOperator *> &list, GoPathSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        QVector<GoOperator*> endList;
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
                this->_analysis->calcAccumulativeProbability(list[i]);
            }
            for (int i = 0; i < endList.size(); ++i)
            {
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    if (endList[i]->accmulatives()->at(j)->accumulative(1) > 1.0 - 1e-8)
                    {
                        tempPath.setTotalProbablity(normals[endList[i]->realID()]->at(j));
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
    if (!GoOperatorFactory::isLogical(list[index]->type()))
    {
        GoStatus *copy = new GoStatus();
        copy->setNumber(list[index]->status()->number());
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            copy->setProbability(i, list[index]->status()->probability(i));
            list[index]->status()->setProbability(i, 0.0);
        }
        list[index]->status()->setProbability(1, 1.0);
        tempPath.add(list[index]);
        this->findPathDfs(normals, path, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            list[index]->status()->setProbability(i, copy->probability(i));
        }
        delete copy;
    }
    GoStatus *copy = new GoStatus();
    copy->setNumber(list[index]->status()->number());
    for (int i = 0; i < list[index]->status()->number(); ++i)
    {
        copy->setProbability(i, list[index]->status()->probability(i));
        list[index]->status()->setProbability(i, 0.0);
    }
    list[index]->status()->setProbability(list[index]->status()->number() - 1, 1.0);
    this->findPathDfs(normals, path, list, tempPath, index + 1, number, order);
    for (int i = 0; i < list[index]->status()->number(); ++i)
    {
        list[index]->status()->setProbability(i, copy->probability(i));
    }
    delete copy;
}

GoPathSetSetSet GoGraph::findCut(int order)
{
    GoPathSetSetSet path;
    this->calcAccumulativeProbability();
    if (this->_error != "")
    {
        return path;
    }
    QVector<GoOperator*> list = this->getTopologicalOrder();
    QMap<int, QVector<double>* > fails;
    for (int i = 0; i < list.size(); ++i)
    {
        GoOperator* op = list[i];
        QVector<double> *fail = new QVector<double>();
        for (int i = 0; i < op->output()->number(); ++i)
        {
            fail->push_back(1.0 - op->accmulatives()->at(i)->probability(1));
        }
        fails[op->realID()] = fail;
    }
    GoCutSet tempPath;
    if (order > list.size())
    {
        order = list.size();
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

void GoGraph::findCutDfs(QMap<int, QVector<double> *> &fails, GoPathSetSetSet &cut, QVector<GoOperator *> &list, GoCutSet &tempPath, int index, int number, int order)
{
    if (number == order)
    {
        QVector<GoOperator*> endList;
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
                this->_analysis->calcAccumulativeProbability(list[i]);
            }
            for (int i = 0; i < endList.size(); ++i)
            {
                bool flag = false;
                for (int j = 0; j < list[i]->output()->number(); ++j)
                {
                    int number = endList[i]->accmulatives()->at(j)->number();
                    double a = endList[i]->accmulatives()->at(j)->accumulative(number - 1);
                    double b = endList[i]->accmulatives()->at(j)->accumulative(number - 2);
                    if (a - b >= 1.0 - 1e-8)
                    {
                        tempPath.setTotalProbablity(fails[endList[i]->realID()]->at(j));
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
    if (!GoOperatorFactory::isLogical(list[index]->type()))
    {
        GoStatus *copy = new GoStatus();
        copy->setNumber(list[index]->status()->number());
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            copy->setProbability(i, list[index]->status()->probability(i));
            list[index]->status()->setProbability(i, 0.0);
        }
        list[index]->status()->setProbability(list[index]->status()->number() - 1, 1.0);
        tempPath.add(list[index]);
        this->findCutDfs(fails, cut, list, tempPath, index + 1, number + 1, order);
        tempPath.removeEnd();
        for (int i = 0; i < list[index]->status()->number(); ++i)
        {
            list[index]->status()->setProbability(i, copy->probability(i));
        }
        delete copy;
    }
    GoStatus *copy = new GoStatus();
    copy->setNumber(list[index]->status()->number());
    for (int i = 0; i < list[index]->status()->number(); ++i)
    {
        copy->setProbability(i, list[index]->status()->probability(i));
        list[index]->status()->setProbability(i, 0.0);
    }
    list[index]->status()->setProbability(1, 1.0);
    this->findCutDfs(fails, cut, list, tempPath, index + 1, number, order);
    for (int i = 0; i < list[index]->status()->number(); ++i)
    {
        list[index]->status()->setProbability(i, copy->probability(i));
    }
    delete copy;
}

void GoGraph::print() const
{
    FILE *file = fopen("graph.log", "a");
    fprintf(file, "Operators: \n");
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        fprintf(file, "%d ID: %d Type: %d Real ID: %d Num: %d %d %d\n", i, this->_operator[i]->id(), this->_operator[i]->type(), this->_operator[i]->realID(), this->_operator[i]->input()->number(), this->_operator[i]->subInput()->number(), this->_operator[i]->output()->number());
    }
    fprintf(file, "Signals: \n");
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        fprintf(file, "Operator %d-%d  %d\n", this->_operator[i]->id(), this->_operator[i]->type(), this->_operator[i]->realID());
        for (int j = 0; j < this->_operator[i]->output()->number(); ++j)
        {
            for (int k = 0; k < this->_operator[i]->output()->signal()->at(j)->size(); ++k)
            {
                GoSignal *signal = this->_operator[i]->output()->signal()->at(j)->at(k);
                fprintf(file, "\t%d (%d-%d) - (%d-%d)  %d - %d\n", signal->id(), signal->u()->id(), signal->u()->type(), signal->v()->id(), signal->v()->type(), signal->u()->realID(), signal->v()->realID());
            }
        }
    }
    for (int i = 0; i < 80; ++i)
    {
        fprintf(file, "=");
    }
    fprintf(file, "\n");
    fclose(file);
}

bool GoGraph::saveAsHTML(const QString filePath)
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
    QVector<GoOperator*> list;
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
                GoOperator *temp = list[i];
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
            out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j) << "</td>";
            if (j == 0)
            {
                out << "<td>" << list[i]->accmulatives()->at(0)->accumulative(j) << "</td>";
            }
            else
            {
                out << "<td>" << (list[i]->accmulatives()->at(0)->accumulative(j) - list[i]->accmulatives()->at(0)->accumulative(j - 1)) << "</td>";
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

bool GoGraph::saveAsHTML(const QString filePath, GoPathSetSetSet path)
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
            out << QString("<h2>%1</h2>").arg(path.endList().at(i).op->id()) <<endl;
            out << "<table>" << endl;
            out << "<tr>" << endl;
            out << "<th>" + QObject::tr("No.") + "</th>" << endl;
            out << "<th>" + QObject::tr("Order") + "</th>" << endl;
            out << "<th>" + QObject::tr("ID List") + "</th>" << endl;
            if (path.isCut())
            {
                out << "<th>" + QObject::tr("Breakdown Probability") + "</th>" << endl;
            }
            else
            {
                out << "<th>" + QObject::tr("Normal Probability") + "</th>" << endl;
            }
            out << "<th>" + QObject::tr("Importance") + "</th>" << endl;
            out << "</tr>" << endl;
            for (int j = 0; j < path.list().at(i)->list().size(); ++j)
            {
                out << "<tr>" << endl;
                out << "<td>" + QString("%1").arg(j + 1) + "</td>" << endl;
                out << "<td>" + QString("%1").arg(path.list().at(i)->list().at(j)->order()) + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toIdString() + "</td>" << endl;
                out << "<td>" + path.list().at(i)->list().at(j)->toProbabilityString() + "</td>" << endl;
                out << "<td></td>" << endl;
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
