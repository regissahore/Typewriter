#include "RungeKuttaMarkov18.h"
const double RK_STEP = 0.0001;

RungeKuttaMarkov18::RungeKuttaMarkov18() : RungeKutta(4)
{
    this->setY(0, 1.0);
}

void RungeKuttaMarkov18::setLambda(double l1, double l2, double lb)
{
    this->lambda1 = l1;
    this->lambda2 = l2;
    this->lambdab = lb;
}

void RungeKuttaMarkov18::setMu(double m1, double m2)
{
    this->mu1 = m1;
    this->mu2 = m2;
}

QVector<double> RungeKuttaMarkov18::F(double x, QVector<double> y)
{
    Q_UNUSED(x);
    QVector<double> z;
    z.push_back(mu1 * y[1] + mu2 * y[2] - (lambda1 + lambda2) * y[0]);
    z.push_back(lambda1 * y[0] + mu2 * y[3] - (mu1 + lambda2) * y[1]);
    z.push_back(lambdab * y[0] - mu1 * y[3] - (mu1 + lambda1) * y[2]);
    z.push_back(lambda2 * y[1] - lambda1 * y[2] - (mu1 + mu2) * y[3]);
    return z;
}
