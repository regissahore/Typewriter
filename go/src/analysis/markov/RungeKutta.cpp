#include <cmath>
#include "RungeKutta.h"

RungeKutta::RungeKutta(int n)
{
    for (int i = 0; i < n; ++i)
    {
        y.push_back(0.0);
        inf.push_back(0.0);
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

void RungeKutta::calculateInfinity()
{
    double startX = this->x;
    QVector<double> startY;
    for (int i = 0; i < this->y.size(); ++i)
    {
        startY.push_back(this->y[i]);
        inf[i] = this->y[i] + 1.0;
    }
    for (int i = 0; i < 10000000; ++i)
    {
        bool flag = true;
        for (int j = 0; j < this->y.size(); ++j)
        {
            if (fabs(this->y[j] - inf[j]) > 1e-10)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            break;
        }
        for (int j = 0; j < this->y.size(); ++j)
        {
            inf[j] = this->y[j];
        }
        nextStep();
    }
    for (int i = 0; i < this->y.size(); ++i)
    {
        y[i] = startY[i];
    }
    this->x = startX;
}

double RungeKutta::getInf(int index) const
{
    return this->inf[index];
}

QVector<double>& RungeKutta::getInf()
{
    return this->inf;
}
