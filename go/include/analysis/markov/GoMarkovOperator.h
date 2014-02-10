#ifndef GOMARKOVOPERATOR_H
#define GOMARKOVOPERATOR_H
#include <QVector>
#include "GoOperator.h"
#include "DoubleVector.h"

class QPainter;
class GoMarkovStatus;
class Messager;
class RungeKuttaBreakdown2;
class RungeKuttaBreakdown3;
class RungeKuttaBreakdown4;

class GoMarkovOperator : public GoOperator
{
public:
    GoMarkovOperator();
    virtual ~GoMarkovOperator();
    DoubleVector qualitativeStatus();
    QVector<DoubleVector>* qualitativeOutput();
    void setQualitativeStatus(DoubleVector value);
    void setQualitativeOutput(int index, DoubleVector value);
    DoubleVector getPrevQualitativeStatus(int index = 0);
    DoubleVector getPrevSubQualitativeStatus(int index = 0);
    virtual void initQualitativeOutput();
    virtual void calcQualitativeProbability();
    GoMarkovStatus* markovStatus() const;
    GoMarkovStatus* markovStatus1() const;
    GoMarkovStatus* markovStatus2() const;
    GoMarkovStatus* markovStatus3() const;
    GoMarkovStatus* markovStatus4() const;
    QVector<GoMarkovStatus*>* markovOutputStatus() const;
    int breakdownNum() const;
    void setBreakdownNum(const int value);
    bool isBreakdownCorrelate() const;
    void setBreakdownCorrelate(bool value);
    virtual void calcOutputMarkovStatus(double time);
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GoMarkovOperator* getPrevOperator(int index = 0);
    GoMarkovOperator* getPrevSubOperator(int index = 0);
    int getPrevIndex(int index = 0);
    int getPrevSubIndex(int index = 0);
    GoMarkovStatus* getPrevMarkovStatus(int index = 0);
    GoMarkovStatus* getPrevSubMarkovStatus(int index = 0);
    virtual bool errorDetect();
    bool isGlobalFeedback() const;
    void setIsGlobalFeedback(const bool value);
    virtual void paintParameter(QPainter *painter);
    QString error() const;
    DoubleVector totalFrequencyBreakdown() const;
    void initWithCurrentLambda(double time);
    virtual void initMarkovStatus(double time, double c12 = 0.0);
    virtual void initOutputMarkovStatus();
    virtual void initCalculation(double interval);
    virtual void prepareNextCalculation(int count, double time);
    virtual void finishCalculation();
    void initInfinityMarkovStatus();
    RungeKuttaBreakdown2* rkBreakdown2() const;
    RungeKuttaBreakdown3* rkBreakdown3() const;
    RungeKuttaBreakdown4* rkBreakdown4() const;
    virtual GoMarkovOperator* copy();
    virtual void save(QDomDocument &document, QDomElement &root) override;
    virtual bool tryOpen(QDomElement &root) override;

protected:
    DoubleVector _qualitativeStatus;
    QVector<DoubleVector> _qualitativeOutput;
    QVector<GoMarkovStatus*> *_outputStatus;
    GoMarkovStatus *_markovStatus;
    GoMarkovStatus *_markovStatus1;
    GoMarkovStatus *_markovStatus2;
    GoMarkovStatus *_markovStatus3;
    GoMarkovStatus *_markovStatus4;
    RungeKuttaBreakdown2 *_rkBreakdown2;
    RungeKuttaBreakdown3 *_rkBreakdown3;
    RungeKuttaBreakdown4 *_rkBreakdown4;
    int _breakdownNum;
    bool _isBreakdownCorrelate;
    bool _isGlobalFeedback;
    QString _error;
    void paintMarkovParameter(QPainter *painter);
};

#endif // GOMARKOVOPERATOR_H
