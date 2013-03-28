#include "goanalysis.h"
#include "gooperator.h"
#include "gosignal.h"
#include "goiomodel.h"
#include "gostatus.h"
#include "gooperatorfactory.h"

GOAnalysis::GOAnalysis()
{
}

void GOAnalysis::calcAccumulativeProbability(GOOperator *op)
{
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

void GOAnalysis::calcAccumulativeProbabilityType1(GOOperator *op)
{
    GOStatus *As = op->input()->signal()->at(0)->next(op)->status();
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        Ag->setAccumulative(i, As->accumulative(i) * Ag->probability(1));
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
}

void GOAnalysis::calcAccumulativeProbabilityType2(GOOperator *op)
{
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            GOStatus *Asj = op->input()->signal()->at(j)->next(op)->status();
            val *= 1.0 - Asj->accumulative(i);
        }
        Ag->setAccumulative(i, (float)(1.0 - val));
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
}

void GOAnalysis::calcAccumulativeProbabilityType3(GOOperator *op)
{
    GOStatus *As = op->input()->signal()->at(0)->next(op)->status();
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        Ag->setAccumulative(i, Ag->probability(0) + As->accumulative(i) * Ag->probability(1));
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
}

void GOAnalysis::calcAccumulativeProbabilityType4(GOOperator *op)
{
    Q_UNUSED(op);
}

void GOAnalysis::calcAccumulativeProbabilityType5(GOOperator *op)
{
    GOStatus *Ag = op->status();
    Ag->setAccumulative(0, Ag->probability(0));
    for (int i = 1; i <= Ag->accumulativeNumber(); ++i)
    {
        Ag->setAccumulative(i, Ag->accumulative(i) + Ag->probability(i));
    }
}

void GOAnalysis::calcAccumulativeProbabilityType6(GOOperator *op)
{
    GOStatus *As1 = op->input()->signal()->at(0)->next(op)->status();
    GOStatus *As2 = op->subInput()->signal()->at(0)->next(op)->status();
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (Ag->probability(0) + As2->accumulative(i) * Ag->probability(1)));
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
}

void GOAnalysis::calcAccumulativeProbabilityType7(GOOperator *op)
{
    GOStatus *As1 = op->input()->signal()->at(0)->next(op)->status();
    GOStatus *As2 = op->subInput()->signal()->at(0)->next(op)->status();
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        Ag->setAccumulative(i, As1->accumulative(i) * (Ag->probability(2) + (1 - As2->accumulative(i)) * Ag->probability(1)));
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
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
    GOStatus *Ag = op->status();
    for (int i = 0; i < Ag->accumulativeNumber(); ++i)
    {
        double val = 1.0;
        for (int j = 0; j < op->input()->number(); ++j)
        {
            GOStatus *Asj = op->input()->signal()->at(j)->next(op)->status();
            val *= Asj->accumulative(i);
        }
        Ag->setAccumulative(i, val);
    }
    Ag->setAccumulative(Ag->accumulativeNumber(), 1.0f);
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
