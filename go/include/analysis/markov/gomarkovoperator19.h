#ifndef GOMARKOVOPERATOR19_H
#define GOMARKOVOPERATOR19_H
#include "GoMarkovOperator.h"

class GoMarkovOperator19 : public GoMarkovOperator
{
public:
    GoMarkovOperator19();
    ~GoMarkovOperator19();
    QVector<double>* delta() const;
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    void paintParameter(QPainter *painter);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> *_delta;
    int _deltaNum;
};

#endif // GOMARKOVOPERATOR1_H
