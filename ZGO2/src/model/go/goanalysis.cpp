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
    //TODO
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
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val *= 1.0 - As.at(j)->accumulative(i);
        }
        Ag->setAccumulative(i, (float)(1.0 - val));
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            val *= As[j]->accumulative(i);
        }
        Ag->setAccumulative(i, val);
    }
    Ag->setAccumulative(Ag->number() - 1, 1.0f);
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
