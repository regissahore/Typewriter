#include <QObject>
#include "gograph.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goiomodel.h"
#include "goanalysis.h"
#include "gooperatorfactory.h"

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
