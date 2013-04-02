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
        QVector<GOOperator*> commonList = this->getCommonSignalList(list[i]);
        analysis->calcAccumulativeProbability(list[i]);
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
    QVector<int> colors;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        colors.push_back(-1);
    }
    for (int i = 0; i < this->_source.size(); ++i)
    {
        if (this->isContainCycleDfs(colors, this->_source[i], i))
        {
            this->_error = QObject::tr("The GO graph contains cycle. ");
            return false;
        }
    }
    for (int i = 0; i < colors.size(); ++i)
    {
        if (colors[i] == -1)
        {
            this->_error = QObject::tr("The GO graph is not connected. ");
            return false;
        }
    }
    return true;
}

/**
 * The depth-first search for checking loop.
 * @param colors The record of the visiting.
 * @param index The index of the operator.
 * @param color The color of the source.
 * @return Returns true if the graph contains loop, otherwise false.
 */
bool GOGraph::isContainCycleDfs(QVector<int> &colors, int index, int color)
{
    colors[index] = color;
    GOOperator *op = this->_operator[index];
    for (int i = 0; i < op->output()->number(); ++i)
    {
        for (int j = 0; j < op->output()->signal()->at(i)->size(); ++j)
        {
            GOOperator *nextOpeartor = op->output()->signal()->at(i)->at(j)->next(op);
            int next = this->_operatorPos[nextOpeartor];
            if (colors[next] == color)
            {
                return true;
            }
            if (colors[next] == -1)
            {
                if (this->isContainCycleDfs(colors, next, color))
                {
                    return true;
                }
            }
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
    QVector<GOOperator*> inside;
    QVector<bool> isInside;
    QVector<bool> isOutside;
    for (int i = 0; i < this->_operator.size(); ++i)
    {
        isInside.push_back(false);
        isOutside.push_back(false);
    }
    for (int i = 0; i < this->_source.size(); ++i)
    {
        GOOperator *op = this->_operator[this->_source[i]];
        int index = this->_operatorPos[op];
        isInside[index] = true;
        inside.push_back(op);
    }
    while (inside.size() > 0)
    {
        for (int i = inside.size() - 1; i >= 0; --i)
        {
            bool flag = true;
            for (int j = 0; j < inside[i]->input()->number() && flag; ++j)
            {
                GOOperator *prevOp = inside[i]->input()->signal()->at(j)->next(inside[i]);
                int prev = this->_operatorPos[prevOp];
                if (!isOutside[prev])
                {
                    flag = false;
                }
            }
            for (int j = 0; j < inside[i]->subInput()->number() && flag; ++j)
            {
                GOOperator *prevOp = inside[i]->subInput()->signal()->at(j)->next(inside[i]);
                int prev = this->_operatorPos[prevOp];
                if (!isOutside[prev])
                {
                    flag = false;
                }
            }
            if (flag)
            {
                int index = this->_operatorPos[inside[i]];
                isOutside[index] = true;
                for (int j = 0; j < inside[i]->output()->number(); ++j)
                {
                    for (int k = 0; k < inside[i]->output()->signal()->at(j)->size(); ++k)
                    {
                        GOOperator *nextOp = inside[i]->output()->signal()->at(j)->at(k)->next(inside[i]);
                        int next = this->_operatorPos[nextOp];
                        if (!isInside[next])
                        {
                            isInside[next] = true;
                            inside.push_back(nextOp);
                        }
                    }
                }
                topList.push_back(inside[i]);
                inside.remove(i);
            }
        }
    }
    return topList;
}

/**
 * Get the ancestor list, the search operator is in the frontest position.
 * @param The operator.
 * @return The vector of the path, which is a vector of operator.
 */
QVector<QVector<GOOperator*> > GOGraph::getAncestorList(GOOperator *op)
{
    if (op->input()->number() == 0)
    {
        QVector<QVector<GOOperator*> > vector;
        QVector<GOOperator*> list;
        list.push_back(op);
        vector.push_back(list);
        return vector;
    }
    QVector<QVector<GOOperator*> > vector;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        QVector<QVector<GOOperator*> > pathList = this->getAncestorList(op->input()->signal()->at(i)->next(op));
        for (int j = 0; j < pathList.size(); ++j)
        {
            pathList[j].push_front(op);
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
QVector<GOOperator*> GOGraph::getCommonSignalList(GOOperator *op)
{
    QVector<QVector<GOOperator*> > ancestorPath = this->getAncestorList(op);
    QVector<GOOperator*> commonList;
    for (int i = 0; i < ancestorPath.size(); ++i)
    {
        for (int j = i + 1; j < ancestorPath.size(); ++j)
        {
            bool findCommon = false;
            for (int ii = 1; ii < ancestorPath[i].size() && !findCommon; ++ii)
            {
                for (int jj = 1; jj < ancestorPath[j].size() && !findCommon; ++jj)
                {
                    if (ancestorPath[i][ii] == ancestorPath[j][jj])
                    {
                        findCommon = true;
                        bool appeared = false;
                        for (int k = 0; k < commonList.size(); ++k)
                        {
                            if (ancestorPath[i][ii] == commonList[k])
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

/**
 * Save the result to a HTML file.
 * @param path The file path.
 * @return Returns true if succeed, otherwise false.
 */
bool GOGraph::saveAsHTML(const QString path)
{
    this->_error = "";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        this->_error = QObject::tr("Can't open file ") + path;
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
            out << QString("<td>%1</td>").arg(list[i]->status()->probability(j));
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
            out << QString("<td>%1</td>").arg(list[i]->accmulatives()->at(0)->accumulative(j));
            if (j == 0)
            {
                out << QString("<td>%1</td>").arg(list[i]->accmulatives()->at(0)->accumulative(j));
            }
            else
            {
                out << QString("<td>%1</td>").arg(list[i]->accmulatives()->at(0)->accumulative(j) - list[i]->accmulatives()->at(0)->accumulative(j - 1));
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
