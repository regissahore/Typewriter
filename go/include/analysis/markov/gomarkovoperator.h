#ifndef GOMARKOVOPERATOR_H
#define GOMARKOVOPERATOR_H
#include <QVector>
#include "GoOperator.h"
#include "DoubleVector.h"

class QPainter;
class GoMarkovStatus;
class Messager;
class RungeKuttaBreakdown3;
class RungeKuttaBreakdown4;

class GoMarkovOperator : public GoOperator
{
public:
    GoMarkovOperator();
    virtual ~GoMarkovOperator();
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
    void initWithCurrentLambda(double time);
    void initMarkovStatus(double time, double c12 = 0.0);
    virtual void calcOutputMarkovStatus(double time);
    virtual void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    virtual void initOutputMarkovStatus();
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
    virtual GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    GoMarkovStatus *_markovStatus;
    QVector<GoMarkovStatus*> *_outputStatus;
    GoMarkovStatus *_markovStatus1;
    GoMarkovStatus *_markovStatus2;
    GoMarkovStatus *_markovStatus3;
    GoMarkovStatus *_markovStatus4;
    RungeKuttaBreakdown3 *_rkBreakdown3;
    RungeKuttaBreakdown4 *_rkBreakdown4;
    int _breakdownNum;
    bool _isBreakdownCorrelate; /** 是否和输入信号有停工相关。*/
    bool _isGlobalFeedback; /** 是否是整体反馈的成员。*/
    QString _error;
    void paintMarkovParameter(QPainter *painter);
};

#endif // GOMARKOVOPERATOR_H
