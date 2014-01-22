#ifndef GOMARKOVOPERATOR23_H
#define GOMARKOVOPERATOR23_H
#include "GoMarkovOperator.h"

class GoMarkovOperator23 : public GoMarkovOperator
{
public:
    GoMarkovOperator23();
    ~GoMarkovOperator23();
    QVector<double>* alpha() const;
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> *_alpha;
};

#endif // GOMARKOVOPERATOR1_H
