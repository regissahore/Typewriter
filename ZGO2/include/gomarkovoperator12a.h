#ifndef GOMARKOVOPERATOR12A_H
#define GOMARKOVOPERATOR12A_H
/**
 * 状态分离器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator12A : public GOMarkovOperator
{
public:
    GOMarkovOperator12A();
    ~GOMarkovOperator12A();
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    bool isUseDelta() const;
    void setIsUseDelta(const bool value);
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(QVector<GOMarkovStatus> prevStatus, double time);
    void paintParameter(QPainter *painter);
    void calcOutputMarkovStatus(double time);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    bool _isUseDelta;
    QVector<QString> *_ids;
    QVector<double> *_delta;
    int _deltaNum;
};

#endif // GOMARKOVOPERATOR12A_H
