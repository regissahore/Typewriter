#ifndef RUNGEKUTTABREAKDOWN4_H
#define RUNGEKUTTABREAKDOWN4_H
/**
 * Runge-Kutta法解三故障模式的方程。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class RungeKuttaBreakdown4
{
public:
    RungeKuttaBreakdown4();
    double rk0() const;
    double rk1() const;
    double rk2() const;
    double rk3() const;
    double rk4() const;
    double calcNormalProbability(double time, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);
    double func0(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);
    double func1(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);
    double func2(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);
    double func3(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);
    double func4(double t, double x0, double x1, double x2, double x3, double x4, double lambda1, double lambda2, double lambda3, double lambda4, double mu1, double mu2, double mu3, double mu4);

protected:
    double _rk0;
    double _rk1;
    double _rk2;
    double _rk3;
    double _rk4;
    double _rkt;
};

#endif // RUNGEKUTTABREAKDOWN4_H
