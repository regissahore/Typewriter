#include "RungeKuttaMarkov9a1.h"
const double RK_STEP = 0.0001;

RungeKuttaMarkov9A1::RungeKuttaMarkov9A1()
{
    this->_rkt = 0.0;
}

double RungeKuttaMarkov9A1::rk0() const
{
    return this->_rk0;
}

double RungeKuttaMarkov9A1::rk1() const
{
    return this->_rk1;
}

double RungeKuttaMarkov9A1::rk2() const
{
    return this->_rk2;
}

double RungeKuttaMarkov9A1::calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2)
{
    if (time < RK_STEP)
    {
        this->_rk0 = 1.0;
        this->_rk1 = 0.0;
        this->_rk2 = 0.0;
        this->_rkt = 0.0;
    }
    while (this->_rkt < time)
    {
        double k1[3], k2[3], k3[3], k4[3];
        k1[0] = func0(this->_rkt, this->_rk0, this->_rk1, this->_rk2,
                      lambda1, lambda2, mu1, mu2);
        k1[1] = func1(this->_rkt, this->_rk0, this->_rk1,
                      lambda1, mu1);
        k1[2] = func2(this->_rkt, this->_rk0, this->_rk2,
                      lambda2, mu2);

        k2[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      lambda1, lambda2, mu1, mu2);
        k2[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      lambda1, mu1);
        k2[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      lambda2, mu2);

        k3[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      lambda1, lambda2, mu1, mu2);
        k3[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      lambda1, mu1);
        k3[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      lambda2, mu2);

        k4[0] = func0(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      lambda1, lambda2, mu1, mu2);
        k4[1] = func1(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      lambda1, mu1);
        k4[2] = func2(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk2 + RK_STEP * k3[2],
                      lambda2, mu2);

        this->_rk0 += RK_STEP / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);;
        this->_rk1 += RK_STEP / 6 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
        this->_rk2 += RK_STEP / 6 * (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]);
        this->_rkt += RK_STEP;
    }
    return this->_rk0;
}

double RungeKuttaMarkov9A1::func0(double t, double x0, double x1, double x2, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    return - (lambda1 + lambda2) * x0 + mu1 * x1 + mu2 * x2;
}

double RungeKuttaMarkov9A1::func1(double t, double x0, double x1, double lambda1, double mu1)
{
    Q_UNUSED(t);
    return lambda1 * x0 - mu1 * x1;
}

double RungeKuttaMarkov9A1::func2(double t, double x0, double x2, double lambda2, double mu2)
{
    Q_UNUSED(t);
    return lambda2 * x0 - mu2 * x2;
}
