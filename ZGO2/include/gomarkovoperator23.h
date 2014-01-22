#ifndef GOMARKOVOPERATOR23_H
#define GOMARKOVOPERATOR23_H
#include "gomarkovoperator.h"

class GOMarkovOperator23 : public GOMarkovOperator
{
public:
    GOMarkovOperator23();
    ~GOMarkovOperator23();
    QVector<double>* alpha() const;
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> *_alpha;
};

#endif // GOMARKOVOPERATOR1_H
