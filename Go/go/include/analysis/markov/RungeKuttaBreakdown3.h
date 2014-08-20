#ifndef RUNGEKUTTABREAKDOWN3_H
#define RUNGEKUTTABREAKDOWN3_H
#include "RungeKutta.h"

class RungeKuttaBreakdown3 : public RungeKutta
{
public:
    RungeKuttaBreakdown3();
    void setLambda(double l1, double l2, double l3);
    void setMu(double m1, double m2, double m3);
    virtual void calculateInfinity() override;
    virtual double getInf(int index) const override;
protected:
    QVector<double> F(double x, QVector<double> y);
private:
    double lambda1, lambda2, lambda3;
    double mu1, mu2, mu3;
};

#endif // RUNGEKUTTABREAKDOWN3_H
