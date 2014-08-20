#ifndef RUNGEKUTTABREAKDOWN4_H
#define RUNGEKUTTABREAKDOWN4_H
#include "RungeKutta.h"

class RungeKuttaBreakdown4 : public RungeKutta
{
public:
    RungeKuttaBreakdown4();
    void setLambda(double l1, double l2, double l3, double l4);
    void setMu(double m1, double m2, double m3, double m4);
    virtual void calculateInfinity() override;
    virtual double getInf(int index) const override;
protected:
    QVector<double> F(double x, QVector<double> y);
private:
    double lambda1, lambda2, lambda3, lambda4;
    double mu1, mu2, mu3, mu4;
};

#endif // RUNGEKUTTABREAKDOWN4_H
