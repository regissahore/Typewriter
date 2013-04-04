#include "goanalysis.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gooperatorfactory.h"
#include "goaccumulative.h"
#include "gograph.h"

GOAnalysis::GOAnalysis()
{
}

void GOAnalysis::calcAccumulativeProbability(GOOperator *op)
{
    op->accmulatives()->clear();
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->accmulatives()->push_back(new GOAccumulative());
    }
    switch (op->TypedItem::type())
    {
    case GOOperatorFactory::Operator_Type_1:
        this->calcAccumulativeProbabilityType1(op);
        break;
    case GOOperatorFactory::Operator_Type_2:
        this->calcAccumulativeProbabilityType2(op);
        break;
    case GOOperatorFactory::Operator_Type_3:
        this->calcAccumulativeProbabilityType3(op);
        break;
    case GOOperatorFactory::Operator_Type_4:
        this->calcAccumulativeProbabilityType4(op);
        break;
    case GOOperatorFactory::Operator_Type_5:
        this->calcAccumulativeProbabilityType5(op);
        break;
    case GOOperatorFactory::Operator_Type_6:
        this->calcAccumulativeProbabilityType6(op);
        break;
    case GOOperatorFactory::Operator_Type_7:
        this->calcAccumulativeProbabilityType7(op);
        break;
    case GOOperatorFactory::Operator_Type_8:
        this->calcAccumulativeProbabilityType8(op);
        break;
    case GOOperatorFactory::Operator_Type_9:
        this->calcAccumulativeProbabilityType9(op);
        break;
    case GOOperatorFactory::Operator_Type_10:
        this->calcAccumulativeProbabilityType10(op);
        break;
    case GOOperatorFactory::Operator_Type_11:
        this->calcAccumulativeProbabilityType11(op);
        break;
    case GOOperatorFactory::Operator_Type_12:
        this->calcAccumulativeProbabilityType12(op);
        break;
    case GOOperatorFactory::Operator_Type_13:
        this->calcAccumulativeProbabilityType13(op);
        break;
    case GOOperatorFactory::Operator_Type_14:
        this->calcAccumulativeProbabilityType14(op);
        break;
    case GOOperatorFactory::Operator_Type_15:
        this->calcAccumulativeProbabilityType15(op);
        break;
    case GOOperatorFactory::Operator_Type_16:
        this->calcAccumulativeProbabilityType16(op);
        break;
    case GOOperatorFactory::Operator_Type_17:
        this->calcAccumulativeProbabilityType17(op);
        break;
    default:
        break;
    }
}

void GOAnalysis::calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex)
{
    GOSignal *signal = op->input()->signal()->at(0);
    GOOperator *prev = signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    int accNum = prev->accmulatives()->at(prevIndex)->number();
    int commonNum = commonOperator.size();
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->accmulatives()->push_back(new GOAccumulative());
        op->accmulatives()->at(i)->setNumber(accNum);
    }
    for (int i = 0; i < accNum - 1; ++i)
    {
        long double value = 0.0;
        for (int j = 0; j < (1 << commonNum); ++j)
        {
            QVector<long double> accValues;
            for (int k = 0; k < commonNum; ++k)
            {
                if (j & (1 << k))
                {
                    accValues.push_back(1.0);
                }
                else
                {
                    accValues.push_back(0.0);
                }
            }
            long double factor = calcTempAccumulative(op, -1, commonOperator, commonIndex, accValues, i);
            for (int k = 0; k < commonNum; ++k)
            {
                int temp = commonIndex[k];
                commonIndex[k] = -1;
                long double acc = calcTempAccumulative(commonOperator[k], temp, commonOperator, commonIndex, accValues, i);
                commonIndex[k] = temp;
                if (acc < 0.0)
                {
                    acc = -acc;
                }
                if (accValues[k] > 0.5)
                {
                    factor *= acc;
                }
                else
                {
                    factor *= 1.0 - acc;
                }
            }
            value += factor;
        }
        for (int j = 0; j < op->output()->number(); ++j)
        {
            op->accmulatives()->at(j)->setAccumulative(i, value);
        }
    }
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->accmulatives()->at(i)->setAccumulative(accNum - 1, 1.0);
    }
}

/**
 * Whether there is a common signal in the operator's prev path.
 * @param op The operator.
 * @param index The output index of the operator.
 * @param commonOperator The operators of the common signals.
 * @param commonIndex The indexes of the common signals.
 * @return Returns true if the common signal is appeared, otherwise false.
 */
bool GOAnalysis::isCommonSignalAppeared(GOOperator *op, int index, QVector<GOOperator *> commonOperator, QVector<int> commonIndex)
{
    for (int i = 0; i < commonOperator.size(); ++i)
    {
        if (commonOperator[i] == op && commonIndex[i] == index)
        {
            return true;
        }
    }
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        if (isCommonSignalAppeared(prev, prevIndex, commonOperator, commonIndex))
        {
            return true;
        }
    }
    for (int i = 0; i < op->subInput()->number(); ++i)
    {
        GOSignal *signal = op->subInput()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        if (isCommonSignalAppeared(prev, prevIndex, commonOperator, commonIndex))
        {
            return true;
        }
    }
    return false;
}

/**
 * Calculate the temp accumulative probability.
 * @param op The operator.
 * @param index The output index of the operator.
 * @param commonOperator The operators of the common signals.
 * @param commonIndex The indexes of the common signals.
 * @param accValues The set accumulative probability value of the common signal.
 * @param accIndex The current calculating accumulative probability index.
 * @return The function returns the negetive calculated value when the common signal is not appeared in the operator's parent path, otherwise returns the calculated temp accumulative probability.
 */
long double GOAnalysis::calcTempAccumulative(GOOperator *op, int index, QVector<GOOperator *> &commonOperator, QVector<int> &commonIndex, QVector<long double> &accValues, int accIndex)
{
    for (int i = 0; i < commonOperator.size(); ++i)
    {
        if (op == commonOperator[i] && index == commonIndex[i])
        {
            return accValues[i];
        }
    }
    bool appeared = false;
    QVector<long double> inputValues;
    QVector<long double> subInputValues;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GOSignal *signal = op->input()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        long double value = calcTempAccumulative(prev, prevIndex, commonOperator, commonIndex, accValues, accIndex);
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
        GOSignal *signal = op->subInput()->signal()->at(i);
        GOOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        long double value = calcTempAccumulative(prev, prevIndex, commonOperator, commonIndex, accValues, accIndex);
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
        switch (op->type())
        {
        case GOOperatorFactory::Operator_Type_1:
            return calcTempAccumulativeType1(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_2:
            return calcTempAccumulativeType2(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_3:
            return calcTempAccumulativeType3(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_4:
            return calcTempAccumulativeType4(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_5:
            return calcTempAccumulativeType5(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_6:
            return calcTempAccumulativeType6(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_7:
            return calcTempAccumulativeType7(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_8:
            return calcTempAccumulativeType8(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_9:
            return calcTempAccumulativeType9(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_10:
            return calcTempAccumulativeType10(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_11:
            return calcTempAccumulativeType11(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_12:
            return calcTempAccumulativeType12(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_13:
            return calcTempAccumulativeType13(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_14:
            return calcTempAccumulativeType14(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_15:
            return calcTempAccumulativeType15(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_16:
            return calcTempAccumulativeType16(op, inputValues, subInputValues, accIndex);
        case GOOperatorFactory::Operator_Type_17:
            return calcTempAccumulativeType17(op, inputValues, subInputValues, accIndex);
        }
    }
    return -op->accmulatives()->at(index)->accumulative(accIndex);
}

void GOAnalysis::calcAccumulativeProbabilityType1(GOOperator *op)
{
    GOStatus *status = op->status();
    GOSignal *signal = op->input()->signal()->at(0);
    GOOperator *prev = signal->next(op);
    GOAccumulative *As = prev->accmulatives()->at(prev->output()->getSignalIndex(signal));
    GOAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As->accumulative(i) * status->probability(1));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType2(GOOperator *op)
{
    QVector<GOSignal*> signal;
    QVector<GOOperator*> prev;
    QVector<GOAccumulative*> As;
    GOAccumulative *Ag = op->accmulatives()->at(0);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        signal.push_back(op->input()->signal()->at(i));
        prev.push_back(signal[i]->next(op));
        As.push_back(prev[i]->accmulatives()->at(prev[i]->output()->getSignalIndex(signal[i])));
    }
    Ag->setNumber(As[0]->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        long double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val *= 1.0 - As.at(j)->accumulative(i);
        }
        Ag->setAccumulative(i, 1.0 - val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType3(GOOperator *op)
{
    GOSignal *signal = op->input()->signal()->at(0);
    GOStatus *status = op->status();
    GOOperator *prev = signal->next(op);
    GOAccumulative *As = prev->accmulatives()->at(prev->output()->getSignalIndex(signal));
    GOAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, status->probability(0) + As->accumulative(i) * status->probability(1));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType4(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType5(GOOperator *op)
{
    GOStatus *status = op->status();
    GOAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(status->number());
    Ag->setAccumulative(0, status->probability(0));
    for (int i = 1; i < Ag->number(); ++i)
    {
        Ag->setAccumulative(i, Ag->accumulative(i - 1) + status->probability(i));
    }
}

void GOAnalysis::calcAccumulativeProbabilityType6(GOOperator *op)
{
    GOStatus *status = op->status();
    GOSignal *signal1 = op->input()->signal()->at(0);
    GOSignal *signal2 = op->subInput()->signal()->at(0);
    GOOperator *prev1 = signal1->next(op);
    GOOperator *prev2 = signal2->next(op);
    GOAccumulative *As1 = prev1->accmulatives()->at(prev1->output()->getSignalIndex(signal1));
    GOAccumulative *As2 = prev2->accmulatives()->at(prev2->output()->getSignalIndex(signal2));
    GOAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As1->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (status->probability(0) + As2->accumulative(i) * status->probability(1)));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType7(GOOperator *op)
{
    GOStatus *status = op->status();
    GOSignal *signal1 = op->input()->signal()->at(0);
    GOSignal *signal2 = op->subInput()->signal()->at(0);
    GOOperator *prev1 = signal1->next(op);
    GOOperator *prev2 = signal2->next(op);
    GOAccumulative *As1 = prev1->accmulatives()->at(prev1->output()->getSignalIndex(signal1));
    GOAccumulative *As2 = prev2->accmulatives()->at(prev2->output()->getSignalIndex(signal2));
    GOAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As1->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (status->probability(2) + (1 - As2->accumulative(i)) * status->probability(1)));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType8(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType9(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType10(GOOperator *op)
{
    QVector<GOSignal*> signal;
    QVector<GOOperator*> prev;
    QVector<GOAccumulative*> As;
    GOAccumulative *Ag = op->accmulatives()->at(0);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        signal.push_back(op->input()->signal()->at(i));
        prev.push_back(signal[i]->next(op));
        As.push_back(prev[i]->accmulatives()->at(prev[i]->output()->getSignalIndex(signal[i])));
    }
    Ag->setNumber(As[0]->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        long double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val *= As[j]->accumulative(i);
        }
        Ag->setAccumulative(i, val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GOAnalysis::calcAccumulativeProbabilityType11(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType12(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType13(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType14(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType15(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType16(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType17(GOOperator *op)
{
    Q_UNUSED(op);
}

long double GOAnalysis::calcTempAccumulativeType1(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return inputValues[0] * op->status()->probability(1);
}

long double GOAnalysis::calcTempAccumulativeType2(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    long double value = 1.0;
    for (int i = 0; i < inputValues.size(); ++i)
    {
        value *= 1.0 - inputValues[i];
    }
    return 1.0 - value;
}

long double GOAnalysis::calcTempAccumulativeType3(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return op->status()->probability(0) + inputValues[0] * op->status()->probability(1);
}

long double GOAnalysis::calcTempAccumulativeType4(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

/**
 * The function should never be used theoretically.
 * @param op
 * @param inputValues
 * @param outputValues
 * @param accIndex
 * @return The temp accumulative probability.
 */
long double GOAnalysis::calcTempAccumulativeType5(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    long double value = 0.0;
    for (int i = 0; i <= accIndex; ++i)
    {
        value += op->status()->probability(i);
    }
    return value;
}

long double GOAnalysis::calcTempAccumulativeType6(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(accIndex);
    return inputValues[0] * (op->status()->probability(0) + subInputValues[0] * op->status()->probability(1));
}

long double GOAnalysis::calcTempAccumulativeType7(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(accIndex);
    return inputValues[0] * (op->status()->probability(2) + (1 - subInputValues[0]) * op->status()->probability(1));
}

long double GOAnalysis::calcTempAccumulativeType8(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType9(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType10(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    double value = 1.0;
    for (int i = 0; i < inputValues.size(); ++i)
    {
        value *= inputValues[i];
    }
    return value;
}

long double GOAnalysis::calcTempAccumulativeType11(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType12(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType13(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType14(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType15(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType16(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

long double GOAnalysis::calcTempAccumulativeType17(GOOperator *op, QVector<long double> inputValues, QVector<long double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}
