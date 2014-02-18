#ifndef RUNGEKUTTAMARKOV18_H
#define RUNGEKUTTAMARKOV18_H
#include <QObject>
#include "RungeKutta.h"

class RungeKuttaMarkov18 : public RungeKutta
{
public:
    RungeKuttaMarkov18();
    void setLambda(double l1, double l2, double lb);
    void setMu(double m1, double m2);
protected:
    QVector<double> F(double x, QVector<double> y) override;
private:
    double lambda1, lambda2, lambdab;
    double mu1, mu2;
};

#endif // RUNGEKUTTAMARKOV18_H
