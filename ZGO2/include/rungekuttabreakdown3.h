#ifndef RUNGEKUTTABREAKDOWN3_H
#define RUNGEKUTTABREAKDOWN3_H
/**
 * Runge-Kutta法解三故障模式的方程。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class RungeKuttaBreakdown3
{
public:
    RungeKuttaBreakdown3();
    double rk0() const;
    double rk1() const;
    double rk2() const;
    double rk3() const;
    double calcNormalProbability(double time, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3);
    double func0(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3);
    double func1(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3);
    double func2(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3);
    double func3(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double lambda3, double mu1, double mu2, double mu3);

protected:
    double _rk0;
    double _rk1;
    double _rk2;
    double _rk3;
    double _rkt;
};

#endif // RUNGEKUTTABREAKDOWN3_H
