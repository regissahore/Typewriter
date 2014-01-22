#ifndef GOMARKOVOPERATOR19_H
#define GOMARKOVOPERATOR19_H
#include "gomarkovoperator.h"

class GOMarkovOperator19 : public GOMarkovOperator
{
public:
    GOMarkovOperator19();
    ~GOMarkovOperator19();
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(GOMarkovStatus prevStatus, double time);
    void paintParameter(QPainter *painter);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<QString> *_ids;
    QVector<double> *_delta;
    int _deltaNum;

    void calcTempOutputMarkovStatus(GOMarkovOperator* op, double time, QString id, double delta, int index);
};

#endif // GOMARKOVOPERATOR1_H
