#include "RungeKuttaBreakdown2.h"

RungeKuttaBreakdown2::RungeKuttaBreakdown2() : RungeKutta(3)
{
    this->setY(0, 1.0);
}

void RungeKuttaBreakdown2::setLambda(double l1, double l2)
{
    lambda1 = l1;
    lambda2 = l2;
}

void RungeKuttaBreakdown2::setMu(double m1, double m2)
{
    mu1 = m1;
    mu2 = m2;
}

void RungeKuttaBreakdown2::calculateInfinity()
{
}

double RungeKuttaBreakdown2::getInf(int index) const
{
    Q_UNUSED(index);
    return mu1 * mu2 /
            (mu1 * mu2 +
             lambda1 * mu2 +
             lambda2 * mu1);
}

QVector<double> RungeKuttaBreakdown2::F(double x, QVector<double> y)
{
    Q_UNUSED(x);
    QVector<double> z;
    z.push_back(-(lambda1 + lambda2) * y[0] + mu1 * y[1] + mu2 * y[2]);
    z.push_back(lambda1 * y[0] - mu1 * y[1]);
    z.push_back(lambda2 * y[0] - mu2 * y[2]);
    return z;
}
