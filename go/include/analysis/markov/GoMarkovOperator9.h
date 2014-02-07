#ifndef GOMARKOVOPERATOR9_H
#define GOMARKOVOPERATOR9_H
#include "GoMarkovOperator.h"

class RungeKuttaBreakdown2;
class RungeKuttaBreakdown3;
class RungeKuttaBreakdown4;

class GoMarkovOperator9 : public GoMarkovOperator
{
public:
    GoMarkovOperator9();
    ~GoMarkovOperator9();
    GoMarkovOperator* copy();
    int feedbackNum() const;
    void setFeedbackNum(int value);
    GoMarkovStatus* feedbackStatus() const;
    GoMarkovStatus* feedbackStatus1() const;
    GoMarkovStatus* feedbackStatus2() const;
    GoMarkovStatus* feedbackStatus3() const;
    GoMarkovStatus* feedbackStatus4() const;
    virtual void initMarkovStatus(double time, double c12 = 0.0);
    virtual void initCalculation(double interval);
    virtual void prepareNextCalculation(int count, double time);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    int _feedbackNum;
    int _calculateCount;
    GoMarkovStatus *_feedbackStatus;
    GoMarkovStatus *_feedbackStatus1;
    GoMarkovStatus *_feedbackStatus2;
    GoMarkovStatus *_feedbackStatus3;
    GoMarkovStatus *_feedbackStatus4;
    RungeKuttaBreakdown2 *_rkFeedback2;
    RungeKuttaBreakdown3 *_rkFeedback3;
    RungeKuttaBreakdown4 *_rkFeedback4;
    DoubleVector _lambdaS1Sum;
    DoubleVector _muS1Sum;
    DoubleVector lambdaS1;
    DoubleVector muS1;
};

#endif // GOMARKOVOPERATOR1_H
