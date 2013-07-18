#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator2 : public GOMarkovOperator
{
public:
    GOMarkovOperator2();
    ~GOMarkovOperator2();
    bool isDualBreakdown() const;
    bool isBreakdownCorrelate() const;
    void setDualBreakdown(bool value);
    void setBreakdownCorrelate(bool value);
    GOMarkovStatus* markovStatus2() const;
    void initMarkovStatus(double time, double c12);
    void calcOutputMarkovStatus(double time);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    bool _isDualBreakdown; /*! 是否是两故障模式。*/
    bool _isBreakdownCorrelate; /*! 是否和输入信号有停工相关。*/
    GOMarkovStatus *_markovStatus2;
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusDual();
    void calcOutputMarkovStatusCorrelate();
};

#endif // GOMARKOVOPERATOR1_H
