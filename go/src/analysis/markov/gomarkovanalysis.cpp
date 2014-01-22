#include <QVector>
#include <qmath.h>
#include "GoMarkovAnalysis.h"
#include "GoOperator.h"
#include "GoSignal.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoMarkovOperator.h"
#include "GoMarkovStatus.h"
#include "GoAccumulative.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovAnalysis::GoMarkovAnalysis() : GoAnalysis()
{
}

void GoMarkovAnalysis::calcMarkovStatus(GoMarkovOperator *op, QVector<GoOperator *> commonOperator, QVector<int> commonIndex, double time)
{
    int commonNum = commonOperator.size();
    QVector<DoubleVector> value;
    for (int i = 0; i < op->output()->number(); ++i)
    {
        value.push_back(0.0);
    }
    for (int i = 0; i < (1 << commonNum); ++i)
    {
        QVector<DoubleVector> normalValues;
        for (int j = 0; j < commonNum; ++j)
        {
            if (i & (1 << j))
            {
                normalValues.push_back(1.0);
            }
            else
            {
                normalValues.push_back(0.0);
            }
        }
        for (int k = 0; k < op->output()->number(); ++k)
        {
            DoubleVector factor = calcTempMarkovStatus(op, k, commonOperator, commonIndex, normalValues, time);
            for (int j = 0; j < commonNum; ++j)
            {
                int temp = commonIndex[j];
                commonIndex[j] = -1;
                DoubleVector normal = calcTempMarkovStatus((GoMarkovOperator*)commonOperator[j], temp, commonOperator, commonIndex, normalValues, time);
                commonIndex[j] = temp;
                if (normal < 0.0)
                {
                    normal = -normal;
                }
                if (normalValues[j] < 0.5)
                {
                    normal = 1.0 - normal;
                }
                factor = factor * normal;
            }
            value[k] += factor;
        }
    }
    op->calcCommonOutputMarkovStatus(value);
}

DoubleVector GoMarkovAnalysis::calcTempMarkovStatus(GoMarkovOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<DoubleVector> &normalValues, double time)
{
    for (int i = 0; i < commonOperator.size(); ++i)
    {
        if (op == commonOperator[i] && index == commonIndex[i])
        {
            return normalValues[i];
        }
    }
    bool appeared = false;
    QVector<DoubleVector> inputValues;
    QVector<DoubleVector> subInputValues;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GoSignal *signal = op->input()->signal()->at(i);
        GoOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        DoubleVector value = calcTempMarkovStatus((GoMarkovOperator*)prev, prevIndex, commonOperator, commonIndex, normalValues, time);
        if (value < 0.0)
        {
            inputValues.push_back(-value);
        }
        else
        {
            appeared = true;
            inputValues.push_back(value);
        }
    }
    for (int i = 0; i < op->subInput()->number(); ++i)
    {
        GoSignal *signal = op->subInput()->signal()->at(i);
        GoOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        DoubleVector value = calcTempMarkovStatus((GoMarkovOperator*)prev, prevIndex, commonOperator, commonIndex, normalValues, time);
        if (value < 0.0)
        {
            subInputValues.push_back(-value);
        }
        else
        {
            appeared = true;
            subInputValues.push_back(value);
        }
    }
    if (appeared)
    {
        return op->calcTempOutputMarkovStatus(time, inputValues, subInputValues, index);
    }
    return -op->markovOutputStatus()->at(index)->probabilityNormal();
}
