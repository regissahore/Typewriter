#ifndef GOANALYSIS_H
#define GOANALYSIS_H
/**
 * Used for analysis the GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
class GOOperator;
class GOAccumulative;

class GOAnalysis
{
public:
    GOAnalysis();
    void calcAccumulativeProbability(GOOperator *op);
    void calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex);

protected:
    bool isCommonSignalAppeared(GOOperator *op, int index, QVector<GOOperator *> commonOperator, QVector<int> commonIndex);
    double calcTempAccumulative(GOOperator *op, int index, QVector<GOOperator *> &commonOperator, QVector<int> &commonIndex, QVector<double> &accValues, int accIndex);
    virtual void calcAccumulativeProbabilityType1(GOOperator *op);
    virtual void calcAccumulativeProbabilityType2(GOOperator *op);
    virtual void calcAccumulativeProbabilityType3(GOOperator *op);
    virtual void calcAccumulativeProbabilityType4(GOOperator *op);
    virtual void calcAccumulativeProbabilityType5(GOOperator *op);
    virtual void calcAccumulativeProbabilityType6(GOOperator *op);
    virtual void calcAccumulativeProbabilityType7(GOOperator *op);
    virtual void calcAccumulativeProbabilityType8(GOOperator *op);
    virtual void calcAccumulativeProbabilityType9(GOOperator *op);
    virtual void calcAccumulativeProbabilityType10(GOOperator *op);
    virtual void calcAccumulativeProbabilityType11(GOOperator *op);
    virtual void calcAccumulativeProbabilityType12(GOOperator *op);
    virtual void calcAccumulativeProbabilityType13(GOOperator *op);
    virtual void calcAccumulativeProbabilityType14(GOOperator *op);
    virtual void calcAccumulativeProbabilityType15(GOOperator *op);
    virtual void calcAccumulativeProbabilityType16(GOOperator *op);
    virtual void calcAccumulativeProbabilityType17(GOOperator *op);

    virtual double calcTempAccumulativeType1(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType2(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType3(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType4(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType5(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType6(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType7(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType8(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType9(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType10(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType11(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType12(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType13(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType14(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType15(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType16(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
    virtual double calcTempAccumulativeType17(GOOperator *op, QVector<double> inputValues, QVector<double> subInputValues, int accIndex);
};

#endif // GOANALYSIS_H
