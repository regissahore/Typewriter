#ifndef GOMARKOVOPERATOR12A_H
#define GOMARKOVOPERATOR12A_H
#include "GoMarkovOperator.h"

class GoMarkovOperator12A : public GoMarkovOperator
{
public:
    GoMarkovOperator12A();
    ~GoMarkovOperator12A();
    virtual void calcQualitativeProbability() override final;
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    bool isUseDelta() const;
    void setIsUseDelta(const bool value);
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(QVector<GoMarkovStatus> prevStatus, double time);
    virtual void paintParameter(QPainter *painter) override final;
    virtual void calcOutputMarkovStatus(double time) override final;
    virtual DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index) override final;
    virtual GoMarkovOperator* copy() override final;
    virtual void save(QDomDocument &document, QDomElement &root) override final;
    virtual bool tryOpen(QDomElement &root) override final;

protected:
    bool _isUseDelta;
    QVector<QString> *_ids;
    QVector<double> *_delta;
    int _deltaNum;
};

#endif // GOMARKOVOPERATOR12A_H
