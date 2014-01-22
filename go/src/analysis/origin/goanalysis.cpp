#include "GoAnalysis.h"
#include "GoOperator.h"
#include "GoSignal.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoOperatorFactory.h"
#include "GoAccumulative.h"
#include "GoGraph.h"
#include "GoParameter.h"
#include "GoMarkovOperatorFactory.h"

GoAnalysis::GoAnalysis()
{
}

GoAnalysis::~GoAnalysis()
{
}

void GoAnalysis::calcAccumulativeProbability(GoOperator *op)
{
    op->accmulatives()->clear();
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->accmulatives()->push_back(new GoAccumulative());
    }
    switch (op->TypedItem::type())
    {
    case GoOperatorFactory::Operator_Type_1:
        this->calcAccumulativeProbabilityType1(op);
        break;
    case GoOperatorFactory::Operator_Type_2:
        this->calcAccumulativeProbabilityType2(op);
        break;
    case GoOperatorFactory::Operator_Type_3:
        this->calcAccumulativeProbabilityType3(op);
        break;
    case GoOperatorFactory::Operator_Type_4:
        this->calcAccumulativeProbabilityType4(op);
        break;
    case GoOperatorFactory::Operator_Type_5:
        this->calcAccumulativeProbabilityType5(op);
        break;
    case GoOperatorFactory::Operator_Type_6:
        this->calcAccumulativeProbabilityType6(op);
        break;
    case GoOperatorFactory::Operator_Type_7:
        this->calcAccumulativeProbabilityType7(op);
        break;
    case GoOperatorFactory::Operator_Type_8:
        this->calcAccumulativeProbabilityType8(op);
        break;
    case GoOperatorFactory::Operator_Type_9:
        this->calcAccumulativeProbabilityType9(op);
        break;
    case GoOperatorFactory::Operator_Type_10:
        this->calcAccumulativeProbabilityType10(op);
        break;
    case GoOperatorFactory::Operator_Type_11:
        this->calcAccumulativeProbabilityType11(op);
        break;
    case GoOperatorFactory::Operator_Type_12:
        this->calcAccumulativeProbabilityType12(op);
        break;
    case GoOperatorFactory::Operator_Type_13:
        this->calcAccumulativeProbabilityType13(op);
        break;
    case GoOperatorFactory::Operator_Type_14:
        this->calcAccumulativeProbabilityType14(op);
        break;
    case GoOperatorFactory::Operator_Type_15:
        this->calcAccumulativeProbabilityType15(op);
        break;
    case GoOperatorFactory::Operator_Type_16:
        this->calcAccumulativeProbabilityType16(op);
        break;
    case GoOperatorFactory::Operator_Type_17:
        this->calcAccumulativeProbabilityType17(op);
        break;
    default:
        break;
    }
}

void GoAnalysis::calcAccumulativeProbability(GoOperator *op, QVector<GoOperator *> commonOperator, QVector<int> commonIndex)
{
    GoSignal *signal = op->input()->signal()->at(0);
    GoOperator *prev = signal->next(op);
    int prevIndex = prev->output()->getSignalIndex(signal);
    int accNum = prev->accmulatives()->at(prevIndex)->number();
    int commonNum = commonOperator.size();
    for (int i = 0; i < op->output()->number(); ++i)
    {
        op->accmulatives()->push_back(new GoAccumulative());
        op->accmulatives()->at(i)->setNumber(accNum);
    }
    for (int i = 0; i < accNum - 1; ++i)
    {
        double value = 0.0;
        for (int j = 0; j < (1 << commonNum); ++j)
        {
            QVector<double> accValues;
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
            double factor = calcTempAccumulative(op, -1, commonOperator, commonIndex, accValues, i);
            for (int k = 0; k < commonNum; ++k)
            {
                int temp = commonIndex[k];
                commonIndex[k] = -1;
                double acc = calcTempAccumulative(commonOperator[k], temp, commonOperator, commonIndex, accValues, i);
                commonIndex[k] = temp;
                if (acc < 0.0)
                {
                    acc = -acc;
                }
                if (accValues[k] < 0.5)
                {
                    acc = 1.0 - acc;
                }
                factor = factor * acc;
            }
            value = value + factor;
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

bool GoAnalysis::isCommonSignalAppeared(GoOperator *op, int index, QVector<GoOperator *> commonOperator, QVector<int> commonIndex)
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
        GoSignal *signal = op->input()->signal()->at(i);
        GoOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        if (isCommonSignalAppeared(prev, prevIndex, commonOperator, commonIndex))
        {
            return true;
        }
    }
    for (int i = 0; i < op->subInput()->number(); ++i)
    {
        GoSignal *signal = op->subInput()->signal()->at(i);
        GoOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        if (isCommonSignalAppeared(prev, prevIndex, commonOperator, commonIndex))
        {
            return true;
        }
    }
    return false;
}

double GoAnalysis::calcTempAccumulative(GoOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<double> &accValues, int accIndex)
{
    for (int i = 0; i < commonOperator.size(); ++i)
    {
        if (op == commonOperator[i] && index == commonIndex[i])
        {
            return accValues[i];
        }
    }
    bool appeared = false;
    QVector<double> inputValues;
    QVector<double> subInputValues;
    for (int i = 0; i < op->input()->number(); ++i)
    {
        GoSignal *signal = op->input()->signal()->at(i);
        GoOperator *prev = signal->next(op);
        int prevIndex = prev->output()->getSignalIndex(signal);
        double value = calcTempAccumulative(prev, prevIndex, commonOperator, commonIndex, accValues, accIndex);
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
        double value = calcTempAccumulative(prev, prevIndex, commonOperator, commonIndex, accValues, accIndex);
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
        case GoOperatorFactory::Operator_Type_1:
            return calcTempAccumulativeType1(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_2:
            return calcTempAccumulativeType2(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_3:
            return calcTempAccumulativeType3(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_4:
            return calcTempAccumulativeType4(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_5:
            return calcTempAccumulativeType5(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_6:
            return calcTempAccumulativeType6(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_7:
            return calcTempAccumulativeType7(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_8:
            return calcTempAccumulativeType8(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_9:
            return calcTempAccumulativeType9(op, index, commonOperator, commonIndex, accValues, accIndex);
        case GoOperatorFactory::Operator_Type_10:
            return calcTempAccumulativeType10(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_11:
            return calcTempAccumulativeType11(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_12:
            return calcTempAccumulativeType12(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_13:
            return calcTempAccumulativeType13(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_14:
            return calcTempAccumulativeType14(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_15:
            return calcTempAccumulativeType15(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_16:
            return calcTempAccumulativeType16(op, inputValues, subInputValues, accIndex);
        case GoOperatorFactory::Operator_Type_17:
            return calcTempAccumulativeType17(op, inputValues, subInputValues, accIndex);
        }
    }
    return -op->accmulatives()->at(index)->accumulative(accIndex);
}

void GoAnalysis::calcAccumulativeProbabilityType1(GoOperator *op)
{
    GoStatus *status = op->status();
    GoSignal *signal = op->input()->signal()->at(0);
    GoOperator *prev = signal->next(op);
    GoAccumulative *As = prev->accmulatives()->at(prev->output()->getSignalIndex(signal));
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As->accumulative(i) * status->probability(1));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType2(GoOperator *op)
{
    QVector<GoSignal*> signal;
    QVector<GoOperator*> prev;
    QVector<GoAccumulative*> As;
    GoAccumulative *Ag = op->accmulatives()->at(0);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        signal.push_back(op->input()->signal()->at(i));
        prev.push_back(signal[i]->next(op));
        As.push_back(prev[i]->accmulatives()->at(prev[i]->output()->getSignalIndex(signal[i])));
    }
    Ag->setNumber(As[0]->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val = val * (1.0 - As.at(j)->accumulative(i));
        }
        Ag->setAccumulative(i, 1.0 - val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType3(GoOperator *op)
{
    GoSignal *signal = op->input()->signal()->at(0);
    GoStatus *status = op->status();
    GoOperator *prev = signal->next(op);
    GoAccumulative *As = prev->accmulatives()->at(prev->output()->getSignalIndex(signal));
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, status->probability(0) + As->accumulative(i) * status->probability(1));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType4(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType5(GoOperator *op)
{
    GoStatus *status = op->status();
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(status->number());
    Ag->setAccumulative(0, status->probability(0));
    for (int i = 1; i < Ag->number(); ++i)
    {
        Ag->setAccumulative(i, Ag->accumulative(i - 1) + status->probability(i));
    }
}

void GoAnalysis::calcAccumulativeProbabilityType6(GoOperator *op)
{
    GoStatus *status = op->status();
    GoSignal *signal1 = op->input()->signal()->at(0);
    GoSignal *signal2 = op->subInput()->signal()->at(0);
    GoOperator *prev1 = signal1->next(op);
    GoOperator *prev2 = signal2->next(op);
    GoAccumulative *As1 = prev1->accmulatives()->at(prev1->output()->getSignalIndex(signal1));
    GoAccumulative *As2 = prev2->accmulatives()->at(prev2->output()->getSignalIndex(signal2));
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As1->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (status->probability(0) + As2->accumulative(i) * status->probability(1)));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType7(GoOperator *op)
{
    GoStatus *status = op->status();
    GoSignal *signal1 = op->input()->signal()->at(0);
    GoSignal *signal2 = op->subInput()->signal()->at(0);
    GoOperator *prev1 = signal1->next(op);
    GoOperator *prev2 = signal2->next(op);
    GoAccumulative *As1 = prev1->accmulatives()->at(prev1->output()->getSignalIndex(signal1));
    GoAccumulative *As2 = prev2->accmulatives()->at(prev2->output()->getSignalIndex(signal2));
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(As1->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (status->probability(2) + (1.0 - As2->accumulative(i)) * status->probability(1)));
    }
    Ag->setAccumulative(Ag->number() - 1,1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType8(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType9(GoOperator *op)
{
    GoSignal *inputSignal = op->input()->signal()->at(0);
    GoSignal *subInputSignal = op->subInput()->signal()->at(0);
    GoOperator *prevInput = inputSignal->next(op);
    GoOperator *prevSubInput = subInputSignal->next(op);
    int prevIndex = prevInput->output()->getSignalIndex(inputSignal);
    int prevSubIndex = prevSubInput->output()->getSignalIndex(subInputSignal);
    GoAccumulative *inputAcc = prevInput->accmulatives()->at(prevIndex);
    GoAccumulative *subInputAcc = prevSubInput->accmulatives()->at(prevSubIndex);
    GoAccumulative *Ag = op->accmulatives()->at(0);
    Ag->setNumber(inputAcc->number());
    for (int i = 0; i < inputAcc->number(); ++i)
    {
        for (int j = 0; j < subInputAcc->number(); ++j)
        {
            for (int k = 0; k < op->parameter()->number(); k += 2)
            {
                if (j - i == (int)op->parameter()->parameter(k))
                {
                    int index = i + (int)op->parameter()->parameter(k + 1);
                    if (index < 0)
                    {
                        index = 0;
                    }
                    if (index >= Ag->number())
                    {
                        index = Ag->number() - 1;
                    }
                    Ag->setAccumulative(index, Ag->accumulative(index) + inputAcc->probability(i) * subInputAcc->probability(j));
                }
            }
        }
    }
    for (int i = 1; i < Ag->number() - 1; ++i)
    {
        Ag->setAccumulative(i, Ag->accumulative(i) + Ag->accumulative(i - 1));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType10(GoOperator *op)
{
    QVector<GoSignal*> signal;
    QVector<GoOperator*> prev;
    QVector<GoAccumulative*> As;
    GoAccumulative *Ag = op->accmulatives()->at(0);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        signal.push_back(op->input()->signal()->at(i));
        prev.push_back(signal[i]->next(op));
        As.push_back(prev[i]->accmulatives()->at(prev[i]->output()->getSignalIndex(signal[i])));
    }
    Ag->setNumber(As[0]->number());
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val = val * As[j]->accumulative(i);
        }
        Ag->setAccumulative(i, val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType11(GoOperator *op)
{
    QVector<GoSignal*> signal;
    QVector<GoOperator*> prev;
    QVector<GoAccumulative*> As;
    GoAccumulative *Ag = op->accmulatives()->at(0);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        signal.push_back(op->input()->signal()->at(i));
        prev.push_back(signal[i]->next(op));
        As.push_back(prev[i]->accmulatives()->at(prev[i]->output()->getSignalIndex(signal[i])));
    }
    Ag->setNumber(As[0]->number());
    int inputNum = op->input()->number();
    int K = op->parameter()->parameter(0);
    for (int i = 0; i < Ag->number() - 1; ++i)
    {
        double val = 0.0;
        for (int j = 0; j < (1 << inputNum); ++j)
        {
            int count = 0;
            for (int k = 0; k < inputNum; ++k)
            {
                if (j & (1 << k))
                {
                    ++count;
                }
            }
            if (count >= K)
            {
                double temp = 1.0;
                for (int k = 0; k < inputNum; ++k)
                {
                    if (j & (1 << k))
                    {
                        temp = temp * As[k]->accumulative(i);
                    }
                    else
                    {
                        temp = temp * (1.0 - As[k]->accumulative(i));
                    }
                }
                val = val + temp;
            }
        }
        Ag->setAccumulative(i, val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0);
}

void GoAnalysis::calcAccumulativeProbabilityType12(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType13(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType14(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType15(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType16(GoOperator *op)
{
    Q_UNUSED(op);
}

void GoAnalysis::calcAccumulativeProbabilityType17(GoOperator *op)
{
    Q_UNUSED(op);
}

double GoAnalysis::calcTempAccumulativeType1(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return inputValues[0] * op->status()->probability(1);
}

double GoAnalysis::calcTempAccumulativeType2(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    double value = 1.0;
    for (int i = 0; i < inputValues.size(); ++i)
    {
        value = value * (1.0 - inputValues[i]);
    }
    return 1.0 - value;
}

double GoAnalysis::calcTempAccumulativeType3(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return op->status()->probability(0) + inputValues[0] * op->status()->probability(1);
}

double GoAnalysis::calcTempAccumulativeType4(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType5(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    double value = 0.0;
    for (int i = 0; i <= accIndex; ++i)
    {
        value = value + op->status()->probability(i);
    }
    return value;
}

double GoAnalysis::calcTempAccumulativeType6(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(accIndex);
    return inputValues[0] * (op->status()->probability(0) + subInputValues[0] * op->status()->probability(1));
}

double GoAnalysis::calcTempAccumulativeType7(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(accIndex);
    return inputValues[0] * (op->status()->probability(2) + (1.0 - subInputValues[0]) * op->status()->probability(1));
}

double GoAnalysis::calcTempAccumulativeType8(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType9(GoOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<double> &accValues, int accIndex)
{
    Q_UNUSED(index);
    GoSignal *inputSignal = op->input()->signal()->at(0);
    GoSignal *subInputSignal = op->subInput()->signal()->at(0);
    GoOperator *inputOperator = inputSignal->next(op);
    GoOperator *subInputOperator = subInputSignal->next(op);
    int inputIndex = inputOperator->output()->getSignalIndex(inputSignal);
    int subInputIndex = subInputOperator->output()->getSignalIndex(subInputSignal);
    int inputStatusNumber = inputOperator->status()->number();
    int subInputStatusNumber = subInputOperator->status()->number();
    int statusNumber = inputStatusNumber > subInputStatusNumber ? inputStatusNumber : subInputStatusNumber;
    QVector<double> inputValues;
    QVector<double> subInputValues;
    for (int i = 0; i < inputStatusNumber; ++i)
    {
        double value = calcTempAccumulative(inputOperator, inputIndex, commonOperator, commonIndex, accValues, i);
        if (value < 0.0)
        {
            inputValues.push_back(-value);
        }
        else
        {
            inputValues.push_back(value);
        }
    }
    for (int i = 0; i < subInputStatusNumber; ++i)
    {
        double value = calcTempAccumulative(subInputOperator, subInputIndex, commonOperator, commonIndex, accValues, i);
        if (value < 0.0)
        {
            subInputValues.push_back(-value);
        }
        else
        {
            subInputValues.push_back(value);
        }
    }
    for (int i = inputStatusNumber - 1; i > 0; --i)
    {
        inputValues[i] = inputValues[i] - inputValues[i - 1];
    }
    for (int i = subInputStatusNumber - 1; i > 0; --i)
    {
        subInputValues[i] = subInputValues[i] = subInputValues[i - 1];
    }
    QVector<double> probability;
    for (int i = 0; i < statusNumber; ++i)
    {
        probability.push_back(0.0);
    }
    for (int i = 0; i < inputStatusNumber; ++i)
    {
        for (int j = 0; j < subInputStatusNumber; ++j)
        {
            for (int k = 0; k < op->parameter()->number(); k += 2)
            {
                if (j - i == (int)op->parameter()->parameter(k))
                {
                    int index = i + (int)op->parameter()->parameter(k + 1);
                    if (index < 0)
                    {
                        index = 0;
                    }
                    if (index >= statusNumber)
                    {
                        index = statusNumber - 1;
                    }
                    probability[index] = probability[index] + inputValues[i] * subInputValues[j];
                }
            }
        }
    }
    for (int i = 1; i < statusNumber; ++i)
    {
        probability[i] = probability[i] + probability[i - 1];
    }
    return probability[accIndex];
}

double GoAnalysis::calcTempAccumulativeType10(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    double value = 1.0;
    for (int i = 0; i < inputValues.size(); ++i)
    {
        value = value * inputValues[i];
    }
    return value;
}

double GoAnalysis::calcTempAccumulativeType11(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    double value = 0.0;
    int inputNum = op->input()->number();
    int K = op->parameter()->parameter(0);
    for (int i = 0; i < (1 << inputNum); ++i)
    {
        int count = 0;
        for (int j = 0; j < inputNum; ++j)
        {
            if (i & (1 << j))
            {
                ++count;
            }
        }
        if (count >= K)
        {
            double temp = 1.0;
            for (int j = 0; j < inputNum; ++j)
            {
                if (i & (1 << j))
                {
                    temp = temp * inputValues[j];
                }
                else
                {
                    temp = temp * (1.0 - inputValues[j]);
                }
            }
            value = value + temp;
        }
    }
    return value;
}

double GoAnalysis::calcTempAccumulativeType12(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType13(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType14(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType15(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType16(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}

double GoAnalysis::calcTempAccumulativeType17(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex)
{
    Q_UNUSED(op);
    Q_UNUSED(inputValues);
    Q_UNUSED(subInputValues);
    Q_UNUSED(accIndex);
    return -1.0;
}
