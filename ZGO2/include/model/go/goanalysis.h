#ifndef GOANALYSIS_H
#define GOANALYSIS_H
/**
 * Used for analysis the GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOOperator;
class GOAccumulative;
class BigDecimal;

class GOAnalysis
{
public:
    GOAnalysis();
    void calcAccumulativeProbability(GOOperator *op);
    void calcAccumulativeProbability(GOOperator *op, QVector<GOOperator *> commonOperator, QVector<int> commonIndex);

protected:
    bool isCommonSignalAppeared(GOOperator *op, int index, QVector<GOOperator *> commonOperator, QVector<int> commonIndex);
    BigDecimal calcTempAccumulative(GOOperator *op, int index, QVector<GOOperator *> &commonOperator, QVector<int> &commonIndex, QVector<BigDecimal> &accValues, int accIndex);
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

    virtual BigDecimal calcTempAccumulativeType1(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType2(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType3(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType4(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType5(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType6(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType7(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType8(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType9(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType10(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType11(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType12(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType13(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType14(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType15(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType16(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
    virtual BigDecimal calcTempAccumulativeType17(GOOperator *op, QVector<BigDecimal> inputValues, QVector<BigDecimal> subInputValues, int accIndex);
};

#endif // GOANALYSIS_H
