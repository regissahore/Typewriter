#include "rungekuttabreakdown3.h"
const double RK_STEP = 0.0001;

RungeKuttaBreakdown3::RungeKuttaBreakdown3()
{
    this->_rkt = 0.0;
}

double RungeKuttaBreakdown3::rk0() const
{
    return 1.0 - this->_rk0;
}

double RungeKuttaBreakdown3::rk1() const
{
    return 1.0 - this->_rk1;
}

double RungeKuttaBreakdown3::rk2() const
{
    return 1.0 - this->_rk2;
}

double RungeKuttaBreakdown3::rk3() const
{
    return 1.0 - this->_rk3;
}

/**
 * Runge-Kutta法解微分方程组。
 * y' = f(t, y), y(t0) = y0
 * y(n + 1) = y(n) + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4)
 * k1 = f(tn, yn)
 * k2 = f(tn + h / 2, yn + h / 2 * k1)
 * k3 = f(tn + h / 2, yn + h / 2 + k2)
 * k4 = f(tn, yn + h * k3)
 * P0(0) = 1.0
 * P1(0) = P2(0) = P3(0) = 0.0
 */
double RungeKuttaBreakdown3::calcNormalProbability(double time, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3)
{
    if (time < RK_STEP)
    {
        this->_rk0 = 0.0;
        this->_rk1 = 1.0;
        this->_rk2 = 1.0;
        this->_rk3 = 1.0;
        this->_rkt = 1.0;
    }
    while (this->_rkt < time)
    {
        double k1[4], k2[4], k3[4], k4[4];
        k1[0] = func0(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k1[1] = func1(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k1[2] = func2(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k1[3] = func3(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);

        k2[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k2[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k2[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k2[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);

        k3[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k3[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k3[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k3[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);

        k4[0] = func0(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k4[1] = func1(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k4[2] = func2(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);
        k4[3] = func3(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, lambda3,
                      mu1, mu2, mu3);

        this->_rk0 += RK_STEP / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);;
        this->_rk1 += RK_STEP / 6 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
        this->_rk2 += RK_STEP / 6 * (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]);
        this->_rk3 += RK_STEP / 6 * (k1[3] + 2 * k2[3] + 2 * k3[3] + k4[3]);
        this->_rkt += RK_STEP;
    }
    return this->rk0();
}

/**
 * Q0'(t) = - (λ1 + λ2 + λ3) + μ1 * Q1(t) + μ2 * Q2(t) + μ3 * Q3(t)
 */
double RungeKuttaBreakdown3::func0(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x0);
    return - (lambda1 + lambda2 + lambda3) + mu1 * x1 + mu2 * x2 + mu3 * x3;
}

/**
 * Q1'(t) = λ1 * Q0(t) + μ1 * Q1(t)
 */
double RungeKuttaBreakdown3::func1(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x2);
    Q_UNUSED(x3);
    Q_UNUSED(lambda2);
    Q_UNUSED(lambda3);
    Q_UNUSED(mu2);
    Q_UNUSED(mu3);
    return lambda1 * x0 + mu1 * x1;
}

/**
 * Q2'(t) = λ2 * Q0(t) + μ2 * Q2(t)
 */
double RungeKuttaBreakdown3::func2(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x3);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda3);
    Q_UNUSED(mu1);
    Q_UNUSED(mu3);
    return lambda2 * x0 + mu2 * x2;
}

/**
 * Q3'(t) = λ3 * Q0(t) + μ3 * Q3(t)
 */
double RungeKuttaBreakdown3::func3(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x2);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda2);
    Q_UNUSED(mu1);
    Q_UNUSED(mu2);
    return lambda3 * x0 + mu3 * x3;
}
