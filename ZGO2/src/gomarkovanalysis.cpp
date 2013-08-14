#include <QVector>
#include <qmath.h>
#include "gomarkovanalysis.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "gomarkovoperator.h"
#include "gomarkovstatus.h"
#include "goaccumulative.h"
#include "gomarkovoperatorfactory.h"

GOMarkovAnalysis::GOMarkovAnalysis() : GOAnalysis()
{
}

void GOMarkovAnalysis::calcMarkovStatus(GOMarkovOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex, double time)
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
                DoubleVector normal = calcTempMarkovStatus((GOMarkovOperator*)commonOperator[j], temp, commonOperator, commonIndex, normalValues, time);
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

DoubleVector GOMarkovAnalysis::calcTempMarkovStatus(GOMarkovOperator *op, int index, QVector<GOOperator *> &commonOperator, QVector<int> &commonIndex, QVector<DoubleVector> &normalValues, double time)
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
    if (GOMarkovOperatorFactory::isVectorInput(op->TypedItem::type()))
    {
        GOSignal *signal = op->input()->signal()->at(0);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        for (int i = 0; i < prev->markovOutputStatus()->size(); ++i)
        {
            DoubleVector value = calcTempMarkovStatus((GOMarkovOperator*)prev, i, commonOperator, commonIndex, normalValues, time);
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
    }
    else
    {
        for (int i = 0; i < op->input()->number(); ++i)
        {
            GOSignal *signal = op->input()->signal()->at(i);
            GOOperator *prev = signal->next(op);
            int prevIndex = prev->output()->getSignalIndex(signal);
            DoubleVector value = calcTempMarkovStatus((GOMarkovOperator*)prev, prevIndex, commonOperator, commonIndex, normalValues, time);
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
    }
    if (GOMarkovOperatorFactory::isVectorSubInput(op->TypedItem::type()))
    {
        GOSignal *signal = op->input()->signal()->at(0);
        GOMarkovOperator *prev = (GOMarkovOperator*)signal->next(op);
        for (int i = 0; i < prev->markovOutputStatus()->size(); ++i)
        {
            DoubleVector value = calcTempMarkovStatus((GOMarkovOperator*)prev, i, commonOperator, commonIndex, normalValues, time);
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
    }
    else
    {
        for (int i = 0; i < op->subInput()->number(); ++i)
        {
            GOSignal *signal = op->subInput()->signal()->at(i);
            GOOperator *prev = signal->next(op);
            int prevIndex = prev->output()->getSignalIndex(signal);
            DoubleVector value = calcTempMarkovStatus((GOMarkovOperator*)prev, prevIndex, commonOperator, commonIndex, normalValues, time);
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
    }
    if (appeared)
    {
        return op->calcTempOutputMarkovStatus(time, inputValues, subInputValues, index);
    }
    return -op->markovOutputStatus()->at(index)->probabilityNormal();
}
