#ifndef GOMARKOVOPERATOR19_H
#define GOMARKOVOPERATOR19_H
/**
 * 超压保护操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator19 : public GOMarkovOperator
{
public:
    GOMarkovOperator19();
    ~GOMarkovOperator19();
    QVector<bool>* isRelevant() const;
    QVector<double>* delta() const;
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    bool errorDetect(Messager *messager);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<bool> *_isRelevant;
    QVector<double> *_delta;
    int _deltaNum;
};

#endif // GOMARKOVOPERATOR1_H
