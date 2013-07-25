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

class GOMarkovOperator : public GOOperator
{
public:
    GOMarkovOperator();
    virtual ~GOMarkovOperator();
    GOMarkovStatus* markovStatus() const;
    GOMarkovStatus* markovStatus1() const;
    GOMarkovStatus* markovStatus2() const;
    QVector<GOMarkovStatus*>* markovOutputStatus() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    bool isDualBreakdown() const;
    void setDualBreakdown(bool value);
    bool isBreakdownCorrelate() const;
    void setBreakdownCorrelate(bool value);
    virtual void initMarkovStatus(double time, double c12 = 0.0);
    virtual void calcOutputMarkovStatus(double time);
    virtual void calcCommonOutputMarkovStatus(QVector<double> PR);
    virtual double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
    virtual void initOutputMarkovStatus();
    GOMarkovOperator* getPrevOperator(int index = 0);
    GOMarkovOperator* getPrevSubOperator(int index = 0);
    GOMarkovStatus* getPrevMarkovStatus(int index = 0);
    GOMarkovStatus* getPrevSubMarkovStatus(int index = 0);
    virtual bool errorDetect(Messager *messager);
    virtual GOMarkovOperator* copy();

protected:
    GOMarkovStatus *_markovStatus;
    QVector<GOMarkovStatus*> *_outputStatus;
    GOMarkovStatus *_markovStatus1;
    GOMarkovStatus *_markovStatus2;
    bool _isDualBreakdown; /*! 是否是两故障模式。*/
    bool _isBreakdownCorrelate; /*! 是否和输入信号有停工相关。*/
};

#endif // GOMARKOVOPERATOR_H
