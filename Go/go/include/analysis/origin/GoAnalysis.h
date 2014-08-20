#ifndef GOANALYSIS_H
#define GOANALYSIS_H
#include "stable.h"

class GoOperator;
class GoAccumulative;

class GoAnalysis
{
public:
    GoAnalysis();
    virtual ~GoAnalysis();
    void calcAccumulativeProbability(GoOperator *op);
    void calcAccumulativeProbability(GoOperator *op, QVector<GoOperator *> commonOperator, QVector<int> commonIndex);

protected:
    bool isCommonSignalAppeared(GoOperator *op, int index, QVector<GoOperator *> commonOperator, QVector<int> commonIndex);
    double calcTempAccumulative(GoOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<double> &accValues, int accIndex);
    virtual void calcAccumulativeProbabilityType1(GoOperator *op);
    virtual void calcAccumulativeProbabilityType2(GoOperator *op);
    virtual void calcAccumulativeProbabilityType3(GoOperator *op);
    virtual void calcAccumulativeProbabilityType4(GoOperator *op);
    virtual void calcAccumulativeProbabilityType5(GoOperator *op);
    virtual void calcAccumulativeProbabilityType6(GoOperator *op);
    virtual void calcAccumulativeProbabilityType7(GoOperator *op);
    virtual void calcAccumulativeProbabilityType8(GoOperator *op);
    virtual void calcAccumulativeProbabilityType9(GoOperator *op);
    virtual void calcAccumulativeProbabilityType10(GoOperator *op);
    virtual void calcAccumulativeProbabilityType11(GoOperator *op);
    virtual void calcAccumulativeProbabilityType12(GoOperator *op);
    virtual void calcAccumulativeProbabilityType13(GoOperator *op);
    virtual void calcAccumulativeProbabilityType14(GoOperator *op);
    virtual void calcAccumulativeProbabilityType15(GoOperator *op);
    virtual void calcAccumulativeProbabilityType16(GoOperator *op);
    virtual void calcAccumulativeProbabilityType17(GoOperator *op);

    virtual double calcTempAccumulativeType1(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType2(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType3(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType4(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType5(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType6(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType7(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType8(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType9(GoOperator *op, int index, QVector<GoOperator *> &commonOperator, QVector<int> &commonIndex, QVector<double> &accValues, int accIndex);
    virtual double calcTempAccumulativeType10(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType11(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType12(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType13(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType14(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType15(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType16(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType17(GoOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
};

#endif // GOANALYSIS_H
