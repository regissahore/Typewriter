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
    QVector<QString>* ids() const;
    QVector<double>* delta() const;
    int deltaNum() const;
    void setDeltaNum(int value);
    void calcOutputMarkovStatus(GOMarkovStatus prevStatus);
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
