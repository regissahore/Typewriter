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
};

#endif // GOANALYSIS_H
