#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#include <QVector>
#include "DoubleVector.h"

class RungeKutta
{
public:
    RungeKutta(int n);
    virtual ~RungeKutta();
    void setX(double value);
    void setY(int index, double value);
    void setH(double value);
    double getY(int index) const;
    QVector<double>& getY();
    void nextStep();
protected:
    virtual QVector<double> F(double x, QVector<double> y);
private:
    double x;
    QVector<double> y;
    double h;
    QVector<double> mul(double x, QVector<double> y);
    QVector<double> add(QVector<double> x, QVector<double> y);
};

#endif // RUNGEKUTTA_H
