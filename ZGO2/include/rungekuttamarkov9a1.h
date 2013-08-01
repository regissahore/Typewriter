#ifndef RUNGEKUTTAMARKOV9A1_H
#define RUNGEKUTTAMARKOV9A1_H
/**
 * Runge-Kutta法解9A1的方程。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class RungeKuttaMarkov9A1
{
public:
    RungeKuttaMarkov9A1();
    double rk0() const;
    double rk1() const;
    double rk2() const;
    double calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2);
    double func0(double t, double x0, double x1, double x2, double lambda1, double lambda2, double mu1, double mu2);
    double func1(double t, double x0, double x1, double lambda1, double mu1);
    double func2(double t, double x0, double x2, double lambda2, double mu2);

protected:
    double _rk0;
    double _rk1;
    double _rk2;
    double _rkt;
};

#endif // RUNGEKUTTAMARKOV9A1_H
