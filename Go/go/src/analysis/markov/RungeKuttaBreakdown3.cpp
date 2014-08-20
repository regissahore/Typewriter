#include "RungeKuttaBreakdown3.h"

RungeKuttaBreakdown3::RungeKuttaBreakdown3() : RungeKutta(4)
{
    this->setY(0, 1.0);
}

void RungeKuttaBreakdown3::setLambda(double l1, double l2, double l3)
{
    lambda1 = l1;
    lambda2 = l2;
    lambda3 = l3;
}

void RungeKuttaBreakdown3::setMu(double m1, double m2, double m3)
{
    mu1 = m1;
    mu2 = m2;
    mu3 = m3;
}

void RungeKuttaBreakdown3::calculateInfinity()
{
}

double RungeKuttaBreakdown3::getInf(int index) const
{
    Q_UNUSED(index);
    return mu1 * mu2 * mu3 /
            (mu1 * mu2 * mu3 +
             lambda1 * mu2 * mu3 +
             lambda2 * mu1 * mu3 +
             lambda3 * mu1 * mu2);
}

QVector<double> RungeKuttaBreakdown3::F(double x, QVector<double> y)
{
    Q_UNUSED(x);
    QVector<double> z;
    z.push_back(-(lambda1 + lambda2 + lambda3) * y[0] + mu1 * y[1] + mu2 * y[2] + mu3 * y[3]);
    z.push_back(lambda1 * y[0] - mu1 * y[1]);
    z.push_back(lambda2 * y[0] - mu2 * y[2]);
    z.push_back(lambda3 * y[0] - mu3 * y[3]);
    return z;
}
