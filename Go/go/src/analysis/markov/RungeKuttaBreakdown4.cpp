#include "RungeKuttaBreakdown4.h"

RungeKuttaBreakdown4::RungeKuttaBreakdown4() : RungeKutta(5)
{
    this->setY(0, 1.0);
}

void RungeKuttaBreakdown4::setLambda(double l1, double l2, double l3, double l4)
{
    lambda1 = l1;
    lambda2 = l2;
    lambda3 = l3;
    lambda4 = l4;
}

void RungeKuttaBreakdown4::setMu(double m1, double m2, double m3, double m4)
{
    mu1 = m1;
    mu2 = m2;
    mu3 = m3;
    mu4 = m4;
}

void RungeKuttaBreakdown4::calculateInfinity()
{
}

double RungeKuttaBreakdown4::getInf(int index) const
{
    Q_UNUSED(index);
    return mu1 * mu2 * mu3 * mu4 /
            (mu1 * mu2 * mu3 * mu4 +
             lambda1 * mu2 * mu3 * mu4 +
             lambda2 * mu1 * mu3 * mu4 +
             lambda3 * mu1 * mu2 * mu4 +
             lambda4 * mu1 * mu2 * mu3);
}

QVector<double> RungeKuttaBreakdown4::F(double x, QVector<double> y)
{
    Q_UNUSED(x);
    QVector<double> z;
    z.push_back(-(lambda1 + lambda2 + lambda3 + lambda4) * y[0] + mu1 * y[1] + mu2 * y[2] + mu3 * y[3] + mu4 * y[4]);
    z.push_back(lambda1 * y[0] - mu1 * y[1]);
    z.push_back(lambda2 * y[0] - mu2 * y[2]);
    z.push_back(lambda3 * y[0] - mu3 * y[3]);
    z.push_back(lambda4 * y[0] - mu4 * y[4]);
    return z;
}
