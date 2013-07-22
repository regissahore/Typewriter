#ifndef GOMARKOVOPERATOR11_H
#define GOMARKOVOPERATOR11_H
/**
 * 两状态单元。有两故障和与输入信号有停工相关两种模式。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator11 : public GOMarkovOperator
{
public:
    GOMarkovOperator11();
    ~GOMarkovOperator11();
    int K() const;
    void setK(int value);
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<double> PR);
    double calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    int _K;
};

#endif // GOMARKOVOPERATOR1_H
