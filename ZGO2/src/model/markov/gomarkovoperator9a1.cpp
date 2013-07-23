#include <qmath.h>
#include "gomarkovoperator9a1.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
const double RK_STEP = 0.001;

GOMarkovOperator9A1::GOMarkovOperator9A1() : GOMarkovOperator9A()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator9A1::~GOMarkovOperator9A1()
{
    this->GOMarkovOperator9A::~GOMarkovOperator9A();
}

void GOMarkovOperator9A1::calcOutputMarkovStatus(double time)
{
    if (this->isBreakdownCorrelate())
    {
        this->calcOutputMarkovStatusBreakdown(time);
    }
    else
    {
        this->calcOutputMarkovStatusNormal(time);
    }
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    if (this->isBreakdownCorrelate())
    {
        return this->calcTempOutputMarkovStatusBreakdown(time);
    }
    return this->calcTempOutputMarkovStatusNormal(time);
}

void GOMarkovOperator9A1::calcOutputMarkovStatusNormal(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double s1 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) + sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double s2 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) - sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double PR = mu1 * mu2 / s1 / s2 +
            (s1 * s1 + (mu1 + mu2) * s1 + mu1 * mu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
            (s2 * s2 + (mu1 + mu2) * s2 + mu1 * mu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    double QR = 1.0 - PR;
    double lambdaR = lambda1 + lambda2;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatusNormal(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double s1 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) + sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double s2 = 0.5 * (-(lambda1 + lambda2 + mu1 + mu2) - sqrt((lambda1 - lambda2 + mu1 - mu2) * (lambda1 - lambda2 + mu1 - mu2) + 4 * lambda1 * lambda2));
    double PR = mu1 * mu2 / s1 / s2 +
            (s1 * s1 + (mu1 + mu2) * s1 + mu1 * mu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
            (s2 * s2 + (mu1 + mu2) * s2 + mu1 * mu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    return PR;
}

void GOMarkovOperator9A1::calcOutputMarkovStatusBreakdown(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double PR = this->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double QR = 1.0 - PR;
    double lambdaR = lambda1 + lambda2;
    double muR = lambdaR * PR / QR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator9A1::calcTempOutputMarkovStatusBreakdown(double time)
{
    GOMarkovStatus *status = this->getPrevMarkovStatus();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    double lambdaC = this->markovStatus()->frequencyBreakdown();
    double muC = this->markovStatus()->frequencyRepair();
    double lambdaF = this->markovStatus()->frequencyBreakdown();
    double muF = this->markovStatus()->frequencyRepair();
    double lambda2 = lambdaC + lambdaF;
    double mu2 = lambda2 * muC * muF / (lambdaC * muF + lambdaF * muC);
    double PR = this->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    return PR;
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
 * P1(0) = P2(0) = 0.0
 */
double GOMarkovOperator9A1::calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2)
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

/**
 * P0(t + Δt) = (1 - λ1 * Δt - λ2 * Δt) * P0(t) + μ1 * Δt * P1(t) + μ2 * Δt * P2(t)
 * P0'(t) = P0(t + Δt) - P0(t)= (1 - λ1 * Δt - λ2 * Δt) * P0(t) + μ1 * Δt * P1(t) + μ2 * Δt * P2(t) - P0(t)
 */
double GOMarkovOperator9A1::func0(double t, double x0, double x1, double x2, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    return (1.0 - lambda1 * RK_STEP - lambda2 * RK_STEP) * x0 +
            mu1 * RK_STEP * x1 +
            mu2 * RK_STEP * x2 -
            x0;
}

/**
 * P1(t + Δt) = λ1 * Δt * P0(t) + (1 - μ1 * Δt) * P1(t)
 * P1'(t) = P1(t + Δt) - P1(t) = λ1 * Δt * P0(t) + (1 - μ1 * Δt) * P1(t) - P1(t)
 */
double GOMarkovOperator9A1::func1(double t, double x0, double x1, double lambda1, double mu1)
{
    Q_UNUSED(t);
    return lambda1 * RK_STEP * x0 + (1.0 - mu1 * RK_STEP) * x1 - x1;
}

/**
 * P2(t + Δt) = λ2 * Δt * P0(t) + (1 - μ2 * Δt) * P2(t)
 * P2'(t) = P2(t + Δt) - P2(t) = λ2 * Δt * P0(t) + (1 - μ2 * Δt) * P2(t) - P2(t)
 */
double GOMarkovOperator9A1::func2(double t, double x0, double x2, double lambda2, double mu2)
{
    Q_UNUSED(t);
    return lambda2 * RK_STEP * x0 + (1.0 - mu2 * RK_STEP) * x2 - x2;
}
