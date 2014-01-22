#ifndef GOMARKOVOPERATOR11_H
#define GOMARKOVOPERATOR11_H
#include "gomarkovoperator.h"

class GOMarkovOperator11 : public GOMarkovOperator
{
public:
    GOMarkovOperator11();
    ~GOMarkovOperator11();
    int K() const;
    int I() const;
    int L() const;
    int J() const;
    void setK(int value);
    void setI(int value);
    void setL(int value);
    void setJ(int value);
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    bool errorDetect();
    void paintParameter(QPainter *painter);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    int _K;
    int _I;
    int _L;
    int _J;
};

#endif // GOMARKOVOPERATOR1_H
