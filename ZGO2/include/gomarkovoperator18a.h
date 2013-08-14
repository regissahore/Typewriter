#ifndef GOMARKOVOPERATOR18A_H
#define GOMARKOVOPERATOR18A_H
/**
 * 备用门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator18A : public GOMarkovOperator
{
public:
    GOMarkovOperator18A();
    ~GOMarkovOperator18A();
    double backup() const;
    void setBackup(double value);
    void calcOutputMarkovStatus(double time);
    void calcCommonOutputMarkovStatus(QVector<DoubleVector> PR);
    DoubleVector calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index);
    GOMarkovOperator* copy();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    double _backup;
};

#endif // GOMARKOVOPERATOR18_H
