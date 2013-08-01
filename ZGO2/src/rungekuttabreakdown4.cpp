#include "rungekuttabreakdown4.h"
const double RK_STEP = 0.0001;

RungeKuttaBreakdown4::RungeKuttaBreakdown4()
{
    this->_rkt = 0.0;
}

double RungeKuttaBreakdown4::rk0() const
{
    return this->_rk0;
}

double RungeKuttaBreakdown4::rk1() const
{
    return this->_rk1;
}

double RungeKuttaBreakdown4::rk2() const
{
    return this->_rk2;
}

double RungeKuttaBreakdown4::rk3() const
{
    return this->_rk3;
}

double RungeKuttaBreakdown4::rk4() const
{
    return this->_rk4;
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
double RungeKuttaBreakdown4::calcNormalProbability(double time, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    if (time < RK_STEP)
    {
        this->_rk0 = 1.0;
        this->_rk1 = 0.0;
        this->_rk2 = 0.0;
        this->_rk3 = 0.0;
        this->_rk4 = 0.0;
        this->_rkt = 0.0;
    }
    while (this->_rkt < time)
    {
        double k1[5], k2[5], k3[5], k4[5];
        k1[0] = func0(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      this->_rk4,
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k1[1] = func1(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      this->_rk4,
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k1[2] = func2(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      this->_rk4,
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k1[3] = func3(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      this->_rk4,
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k1[4] = func4(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      this->_rk4,
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);

        k2[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      this->_rk4 + RK_STEP * 0.5 * k1[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k2[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      this->_rk4 + RK_STEP * 0.5 * k1[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k2[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      this->_rk4 + RK_STEP * 0.5 * k1[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k2[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      this->_rk4 + RK_STEP * 0.5 * k1[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k2[4] = func4(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      this->_rk4 + RK_STEP * 0.5 * k1[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);

        k3[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      this->_rk4 + RK_STEP * 0.5 * k2[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k3[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      this->_rk4 + RK_STEP * 0.5 * k2[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k3[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      this->_rk4 + RK_STEP * 0.5 * k2[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k3[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      this->_rk4 + RK_STEP * 0.5 * k2[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k3[4] = func4(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      this->_rk4 + RK_STEP * 0.5 * k2[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);

        k4[0] = func0(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      this->_rk4 + RK_STEP * k3[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k4[1] = func1(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      this->_rk4 + RK_STEP * k3[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k4[2] = func2(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      this->_rk4 + RK_STEP * k3[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k4[3] = func3(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      this->_rk4 + RK_STEP * k3[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);
        k4[4] = func4(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      this->_rk4 + RK_STEP * k3[4],
                      lambda1, lambda2, lambda3, lambda4,
                      mu1, mu2, mu3, mu4);

        this->_rk0 += RK_STEP / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);;
        this->_rk1 += RK_STEP / 6 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
        this->_rk2 += RK_STEP / 6 * (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]);
        this->_rk3 += RK_STEP / 6 * (k1[3] + 2 * k2[3] + 2 * k3[3] + k4[3]);
        this->_rk4 += RK_STEP / 6 * (k1[4] + 2 * k2[4] + 2 * k3[4] + k4[4]);
        this->_rkt += RK_STEP;
    }
    return this->_rk0;
}

/**
 * P0'(t) = - (λ1 + λ2 + λ3 + λ4) + μ1 * P1(t) + μ2 * P2(t) + μ3 * P3(t) + μ4 * P4(t)
 */
double RungeKuttaBreakdown4::func0(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    Q_UNUSED(t);
    Q_UNUSED(x0);
    return - (lambda1 + lambda2 + lambda3 + lambda4) + mu1 * x1 + mu2 * x2 + mu3 * x3 + mu4 * x4;
}

/**
 * P1'(t) = λ1 * Q0(t) - μ1 * P1(t)
 */
double RungeKuttaBreakdown4::func1(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    Q_UNUSED(t);
    Q_UNUSED(x2);
    Q_UNUSED(x3);
    Q_UNUSED(x4);
    Q_UNUSED(lambda2);
    Q_UNUSED(lambda3);
    Q_UNUSED(lambda4);
    Q_UNUSED(mu2);
    Q_UNUSED(mu3);
    Q_UNUSED(mu4);
    return lambda1 * x0 - mu1 * x1;
}

/**
 * P2'(t) = λ2 * Q0(t) - μ2 * P2(t)
 */
double RungeKuttaBreakdown4::func2(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x3);
    Q_UNUSED(x4);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda3);
    Q_UNUSED(lambda4);
    Q_UNUSED(mu1);
    Q_UNUSED(mu3);
    Q_UNUSED(mu4);
    return lambda2 * x0 - mu2 * x2;
}

/**
 * P3'(t) = λ3 * Q0(t) - μ3 * P3(t)
 */
double RungeKuttaBreakdown4::func3(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x2);
    Q_UNUSED(x4);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda2);
    Q_UNUSED(lambda4);
    Q_UNUSED(mu1);
    Q_UNUSED(mu2);
    Q_UNUSED(mu4);
    return lambda3 * x0 - mu3 * x3;
}

/**
 * P4'(t) = λ4 * Q0(t) - μ4 * P4(t)
 */
double RungeKuttaBreakdown4::func4(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x2);
    Q_UNUSED(x3);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda2);
    Q_UNUSED(lambda3);
    Q_UNUSED(mu1);
    Q_UNUSED(mu2);
    Q_UNUSED(mu3);
    return lambda4 * x0 - mu4 * x4;
}
