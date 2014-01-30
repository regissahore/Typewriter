#include "RungeKutta.h"

RungeKutta::RungeKutta(int n)
{
    for (int i = 0; i < n; ++i)
    {
        y.push_back(0.0);
    }
    x = 0.0;
}

RungeKutta::~RungeKutta()
{
}

void RungeKutta::setX(double value)
{
    x = value;
}

void RungeKutta::setY(int index, double value)
{
    y[index] = value;
}

void RungeKutta::setH(double value)
{
    h = value / 10;
}

double RungeKutta::getY(int index) const
{
    return y[index];
}

QVector<double>& RungeKutta::getY()
{
    return y;
}

void RungeKutta::nextStep()
{
    for (int i = 0; i < 10; ++i)
    {
        QVector<double> K1 = F(x, y);
        QVector<double> K2 = F(x + h / 2, add(y, mul(h / 2, K1)));
        QVector<double> K3 = F(x + h / 2, add(y, mul(h / 2, K2)));
        QVector<double> K4 = F(x + h, add(y, mul(h, K3)));
        y = add(y, mul(h / 6, add(add(K1, mul(2, K2)), add(mul(2, K3), K4))));
        x += h;
    }
}

QVector<double> RungeKutta::F(double x, QVector<double> y)
{
    Q_UNUSED(x);
    return y;
}

QVector<double> RungeKutta::mul(double x, QVector<double> y)
{
    QVector<double> z;
    for (int i = 0; i < y.size(); ++i)
    {
        z.push_back(x * y[i]);
    }
    return z;
}

QVector<double> RungeKutta::add(QVector<double> x, QVector<double> y)
{
    QVector<double> z;
    for (int i = 0; i < y.size(); ++i)
    {
        z.push_back(x[i] + y[i]);
    }
    return z;
}
