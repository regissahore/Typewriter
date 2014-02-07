#ifndef RUNGEKUTTABREAKDOWN2_H
#define RUNGEKUTTABREAKDOWN2_H
#include "RungeKutta.h"

class RungeKuttaBreakdown2 : public RungeKutta
{
public:
    RungeKuttaBreakdown2();
    void setLambda(double l1, double l2);
    void setMu(double m1, double m2);
protected:
    QVector<double> F(double x, QVector<double> y);
private:
    double lambda1, lambda2;
    double mu1, mu2;
};

#endif // RUNGEKUTTABREAKDOWN2_H
