#include <QObject>
#include <QFile>
#include <QTextStream>
#include "gograph.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goiomodel.h"
#include "goanalysis.h"
#include "gooperatorfactory.h"
#include "gostatus.h"

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
        if (op->output()->signal()->at(i) != 0L)
        {
            GOOperator *nextOpeartor = op->output()->signal()->at(i)->next(op);
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
                    if (inside[i]->output()->signal()->at(j) != 0L)
                    {
                        GOOperator *nextOp = inside[i]->output()->signal()->at(j)->next(inside[i]);
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
    out << "<h1>" + file.fileName() + "</h1>" << endl;
    for (int i = 0; i < list.size(); ++i)
    {
        out << QString("<h2>%1-%2</h2>").arg(list[i]->type()).arg(list[i]->id()) << endl;
        out << "<table border = 1>" << endl;
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
        for (int j = 0; j <= list[i]->status()->probablityNumber(); ++j)
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
        out << "<th>" + QObject::tr("Probability") + "</th>" << endl;
        out << "</tr>" << endl;
        for (int j = 0; j <= list[i]->status()->accumulativeNumber(); ++j)
        {
            out << "<tr>" << endl;
            out << QString("<td style='text-align:center;'>%1</td>").arg(j);
            if (j == 0)
            {
                out << QString("<td>%1</td>").arg(list[i]->status()->accumulative(j));
            }
            else
            {
                out << QString("<td>%1</td>").arg(list[i]->status()->accumulative(j) - list[i]->status()->accumulative(j - 1));
            }
            out << "</tr>" << endl;
        }
        out << "</table>" << endl;
        out << "</td>" << endl;
        out << "</tr>" << endl;
        out << "</table>" << endl;
    }
    out << "</body>" << endl;
    out << "</html>" << endl;
    file.close();
    return true;
}
