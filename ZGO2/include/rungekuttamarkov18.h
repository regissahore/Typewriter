#ifndef RUNGEKUTTAMARKOV18_H
#define RUNGEKUTTAMARKOV18_H
/**
 * Runge-Kutta法解18的方程。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QObject>

class RungeKuttaMarkov18
{
public:
    RungeKuttaMarkov18();
    double rk0() const;
    double rk1() const;
    double rk2() const;
    double rk3() const;
    double lambdaB1() const;
    void setLambdaB1(const double value);
    double calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2);
    double func0(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func1(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func2(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);
    double func3(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2);

protected:
    double _rk0;
    double _rk1;
    double _rk2;
    double _rk3;
    double _rkt;
    double _lambdaB1;
};

#endif // RUNGEKUTTAMARKOV18_H
