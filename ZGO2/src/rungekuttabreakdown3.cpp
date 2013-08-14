#include "rungekuttabreakdown3.h"
const DoubleVector RK_STEP = 0.0001;

RungeKuttaBreakdown3::RungeKuttaBreakdown3()
{
    this->_rkt = 0.0;
}

DoubleVector RungeKuttaBreakdown3::rk0() const
{
    return this->_rk0;
}

DoubleVector RungeKuttaBreakdown3::rk1() const
{
    return this->_rk1;
}

DoubleVector RungeKuttaBreakdown3::rk2() const
{
    return this->_rk2;
}

DoubleVector RungeKuttaBreakdown3::rk3() const
{
    return this->_rk3;
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
DoubleVector RungeKuttaBreakdown3::calcNormalProbability(DoubleVector time, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3)
{
    if (time < RK_STEP)
    {
        this->_rk0 = 1.0;
        this->_rk1 = 0.0;
        this->_rk2 = 0.0;
        this->_rk3 = 0.0;
        this->_rkt = 0.0;
    }
    while (this->_rkt < time)
    {
        DoubleVector k1[4], k2[4], k3[4], k4[4];
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
 * P0'(t) = - (λ1 + λ2 + λ3) + μ1 * P1(t) + μ2 * P2(t) + μ3 * P3(t)
 */
DoubleVector RungeKuttaBreakdown3::func0(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x0);
    return - (lambda1 + lambda2 + lambda3) + mu1 * x1 + mu2 * x2 + mu3 * x3;
}

/**
 * P1'(t) = λ1 * P0(t) - μ1 * P1(t)
 */
DoubleVector RungeKuttaBreakdown3::func1(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x2);
    Q_UNUSED(x3);
    Q_UNUSED(lambda2);
    Q_UNUSED(lambda3);
    Q_UNUSED(mu2);
    Q_UNUSED(mu3);
    return lambda1 * x0 - mu1 * x1;
}

/**
 * P2'(t) = λ2 * P0(t) - μ2 * P2(t)
 */
DoubleVector RungeKuttaBreakdown3::func2(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x3);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda3);
    Q_UNUSED(mu1);
    Q_UNUSED(mu3);
    return lambda2 * x0 - mu2 * x2;
}

/**
 * P3'(t) = λ3 * P0(t) - μ3 * P3(t)
 */
DoubleVector RungeKuttaBreakdown3::func3(DoubleVector t, DoubleVector x0, DoubleVector x1, DoubleVector x2, DoubleVector x3, DoubleVector lambda1, DoubleVector lambda2, DoubleVector lambda3, DoubleVector mu1, DoubleVector mu2, DoubleVector mu3)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(x2);
    Q_UNUSED(lambda1);
    Q_UNUSED(lambda2);
    Q_UNUSED(mu1);
    Q_UNUSED(mu2);
    return lambda3 * x0 - mu3 * x3;
}
