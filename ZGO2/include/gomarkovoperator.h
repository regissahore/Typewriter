#ifndef GOMARKOVOPERATOR_H
#define GOMARKOVOPERATOR_H
/**
 * The operator model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "gooperator.h"

class GOMarkovStatus;
class Messager;
class RungeKuttaBreakdown3;
class RungeKuttaBreakdown4;

class GOMarkovOperator : public GOOperator
{
public:
    GOMarkovOperator();
    virtual ~GOMarkovOperator();
    GOMarkovStatus* markovStatus() const;
    GOMarkovStatus* markovStatus1() const;
    GOMarkovStatus* markovStatus2() const;
    GOMarkovStatus* markovStatus3() const;
    GOMarkovStatus* markovStatus4() const;
    QVector<GOMarkovStatus*>* markovOutputStatus() const;
    int breakdownNum() const;
    void setBreakdownNum(const int value);
    bool isBreakdownCorrelate() const;
    void setBreakdownCorrelate(bool value);
    void initMarkovStatus(double time, double c12 = 0.0);
    virtual void calcOutputMarkovStatus(double time);
    virtual void calcCommonOutputMarkovStatus(QVector<double> PR);
    virtual double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
    virtual void initOutputMarkovStatus();
    GOMarkovOperator* getPrevOperator(int index = 0);
    GOMarkovOperator* getPrevSubOperator(int index = 0);
    GOMarkovStatus* getPrevMarkovStatus(int index = 0);
    GOMarkovStatus* getPrevSubMarkovStatus(int index = 0);
    virtual bool errorDetect(Messager *messager);
    bool isGlobalFeedback() const;
    void setIsGlobalFeedback(const bool value);
    virtual GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    GOMarkovStatus *_markovStatus;
    QVector<GOMarkovStatus*> *_outputStatus;
    GOMarkovStatus *_markovStatus1;
    GOMarkovStatus *_markovStatus2;
    GOMarkovStatus *_markovStatus3;
    GOMarkovStatus *_markovStatus4;
    RungeKuttaBreakdown3 *_rkBreakdown3;
    RungeKuttaBreakdown4 *_rkBreakdown4;
    int _breakdownNum;
    bool _isBreakdownCorrelate; /** 是否和输入信号有停工相关。*/
    bool _isGlobalFeedback; /** 是否是整体反馈的成员。*/
};

#endif // GOMARKOVOPERATOR_H
