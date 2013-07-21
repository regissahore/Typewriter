#ifndef GOMARKOVOPERATOR1_H
#define GOMARKOVOPERATOR1_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator1 : public GOMarkovOperator
{
public:
    GOMarkovOperator1();
    ~GOMarkovOperator1();
    QString typeName() const;
    bool isDualBreakdown() const;
    bool isBreakdownCorrelate() const;
    void setDualBreakdown(bool value);
    void setBreakdownCorrelate(bool value);
    GOMarkovStatus* markovStatus2() const;
    void initMarkovStatus(double time, double c12);
    void calcOutputMarkovStatus(double time);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    bool _isDualBreakdown; /*! 是否是两故障模式。*/
    bool _isBreakdownCorrelate; /*! 是否和输入信号有停工相关。*/
    GOMarkovStatus *_markovStatus2;
    void calcOutputMarkovStatusNormal();
    void calcOutputMarkovStatusCorrelate();
    double calcTempOutputMarkovStatusNormal(double PS);
    double calcTempOutputMarkovStatusCorrelate(double PS);
};

#endif // GOMARKOVOPERATOR1_H
