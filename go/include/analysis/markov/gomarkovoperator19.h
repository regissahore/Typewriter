#ifndef GOMARKOVOPERATOR19_H
#define GOMARKOVOPERATOR19_H
#include "GoMarkovOperator.h"

class GoMarkovOperator19 : public GoMarkovOperator
{
public:
    GoMarkovOperator19();
    ~GoMarkovOperator19();
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(GoMarkovStatus prevStatus, double time);
    void paintParameter(QPainter *painter);
    GoMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<QString> *_ids;
    QVector<double> *_delta;
    int _deltaNum;

    void calcTempOutputMarkovStatus(GoMarkovOperator* op, double time, QString id, double delta, int index);
};

#endif // GOMARKOVOPERATOR1_H
