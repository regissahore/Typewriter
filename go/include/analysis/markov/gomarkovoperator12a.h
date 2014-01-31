#ifndef GOMARKOVOPERATOR12A_H
#define GOMARKOVOPERATOR12A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator12A : public GoMarkovOperator
{
public:
    GoMarkovOperator12A();
    ~GoMarkovOperator12A();
    virtual void calcQualitativeProbability();
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    bool isUseDelta() const;
    void setIsUseDelta(const bool value);
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(QVector<GoMarkovStatus> prevStatus, double time);
    void paintParameter(QPainter *painter);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    bool _isUseDelta;
    QVector<QString> *_ids;
    QVector<double> *_delta;
    int _deltaNum;
};

#endif // GOMARKOVOPERATOR12A_H
