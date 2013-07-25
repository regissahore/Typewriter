#include <qmath.h>
#include "gomarkovoperator18.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

const double RK_STEP = 0.0001;

GOMarkovOperator18::GOMarkovOperator18() : GOMarkovOperator()
{
    this->input()->setNumber(2);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_lambdaB1 = 0.0;
}

GOMarkovOperator18::~GOMarkovOperator18()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

double GOMarkovOperator18::lambdaB1() const
{
    return this->_lambdaB1;
}

void GOMarkovOperator18::setLambdaB1(double value)
{
    this->_lambdaB1 = value;
}

void GOMarkovOperator18::calcOutputMarkovStatus(double time)
{
    GOMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    double PS1 = status->probabilityNormal();
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    double lambda2 = status->frequencyBreakdown();
    double mu2 = status->frequencyRepair();
    this->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double PR = PS1 + this->_rk1;
    double lambdaR = (lambda1 * (PS1 - this->_rk0) + lambda2 * this->_rk1) / (PS1 + this->_rk1);
    double muR = mu1 + mu2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator18::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    GOMarkovStatus *status;
    status = this->getPrevMarkovStatus(0);
    double PS1 = input[0];
    double lambda1 = status->frequencyBreakdown();
    double mu1 = status->frequencyRepair();
    status = this->getPrevMarkovStatus(1);
    double lambda2 = status->frequencyBreakdown();
    double mu2 = status->frequencyRepair();
    this->calcNormalProbability(time, lambda1, lambda2, mu1, mu2);
    double PR = PS1 + this->_rk1;
    return PR;
}

GOMarkovOperator* GOMarkovOperator18::copy()
{
    GOMarkovOperator18 *op = new GOMarkovOperator18();
    op->setType(this->TypedItem::type());
    op->input()->setNumber(this->input()->number());
    op->subInput()->setNumber(this->subInput()->number());
    op->output()->setNumber(this->output()->number());

    op->setDualBreakdown(this->isDualBreakdown());
    op->setBreakdownCorrelate(this->isBreakdownCorrelate());

    op->markovStatus()->setProbabilityNormal(this->markovStatus()->probabilityNormal());
    op->markovStatus()->setFrequencyBreakdown(this->markovStatus()->frequencyBreakdown());
    op->markovStatus()->setFrequencyRepair(this->markovStatus()->frequencyRepair());

    op->markovStatus1()->setProbabilityNormal(this->markovStatus1()->probabilityNormal());
    op->markovStatus1()->setFrequencyBreakdown(this->markovStatus1()->frequencyBreakdown());
    op->markovStatus1()->setFrequencyRepair(this->markovStatus1()->frequencyRepair());

    op->markovStatus2()->setProbabilityNormal(this->markovStatus2()->probabilityNormal());
    op->markovStatus2()->setFrequencyBreakdown(this->markovStatus2()->frequencyBreakdown());
    op->markovStatus2()->setFrequencyRepair(this->markovStatus2()->frequencyRepair());

    op->setLambdaB1(this->lambdaB1());
    return op;
}

void GOMarkovOperator18::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->isDualBreakdown());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    element.setAttribute("lambdab1", this->lambdaB1());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
}

bool GOMarkovOperator18::tryOpen(QDomElement &root)
{
    if (root.tagName() != "model")
    {
        return false;
    }
    this->setType(root.attribute("type").toInt());
    this->setId(root.attribute("id").toInt());
    this->input()->setNumber(root.attribute("input").toInt());
    this->subInput()->setNumber(root.attribute("subInput").toInt());
    this->output()->setNumber(root.attribute("output").toInt());
    this->setDualBreakdown(root.attribute("dual").toInt());
    this->setBreakdownCorrelate(root.attribute("breakdown").toInt());
    this->setLambdaB1(root.attribute("lambdab1").toDouble());
    QDomElement element = root.firstChildElement();
    if (!this->status()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus()->tryOpen(element))
    {
        return false;
    }
    if (!this->markovStatus1()->tryOpen(element))
    {
        return false;
    }
    if (!this->markovStatus2()->tryOpen(element))
    {
        return false;
    }
    return true;
}

double GOMarkovOperator18::calcNormalProbability(double time, double lambda1, double lambda2, double mu1, double mu2)
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
        double k1[4], k2[4], k3[4], k4[4];
        k1[0] = func0(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, mu1, mu2);
        k1[1] = func1(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, mu1, mu2);
        k1[2] = func2(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, mu1, mu2);
        k1[3] = func3(this->_rkt,
                      this->_rk0,
                      this->_rk1,
                      this->_rk2,
                      this->_rk3,
                      lambda1, lambda2, mu1, mu2);

        k2[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, mu1, mu2);
        k2[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, mu1, mu2);
        k2[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, mu1, mu2);
        k2[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k1[0],
                      this->_rk1 + RK_STEP * 0.5 * k1[1],
                      this->_rk2 + RK_STEP * 0.5 * k1[2],
                      this->_rk3 + RK_STEP * 0.5 * k1[3],
                      lambda1, lambda2, mu1, mu2);

        k3[0] = func0(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, mu1, mu2);
        k3[1] = func1(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, mu1, mu2);
        k3[2] = func2(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, mu1, mu2);
        k3[3] = func3(this->_rkt + RK_STEP * 0.5,
                      this->_rk0 + RK_STEP * 0.5 * k2[0],
                      this->_rk1 + RK_STEP * 0.5 * k2[1],
                      this->_rk2 + RK_STEP * 0.5 * k2[2],
                      this->_rk3 + RK_STEP * 0.5 * k2[3],
                      lambda1, lambda2, mu1, mu2);

        k4[0] = func0(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, mu1, mu2);
        k4[1] = func1(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, mu1, mu2);
        k4[2] = func2(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, mu1, mu2);
        k4[3] = func3(this->_rkt,
                      this->_rk0 + RK_STEP * k3[0],
                      this->_rk1 + RK_STEP * k3[1],
                      this->_rk2 + RK_STEP * k3[2],
                      this->_rk3 + RK_STEP * k3[3],
                      lambda1, lambda2, mu1, mu2);

        this->_rk0 += RK_STEP / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);;
        this->_rk1 += RK_STEP / 6 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]);
        this->_rk2 += RK_STEP / 6 * (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]);
        this->_rk3 += RK_STEP / 6 * (k1[3] + 2 * k2[3] + 2 * k3[3] + k4[3]);
        this->_rkt += RK_STEP;
    }
    return this->_rk0;
}

double GOMarkovOperator18::func0(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    Q_UNUSED(x3);
    Q_UNUSED(lambda2);
    return mu1 * x1 + mu2 * x2 - (lambda1 + lambdaB1()) * x0;
}

double GOMarkovOperator18::func1(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    Q_UNUSED(x2);
    return lambda1 * x0 + mu2 * x3 - (mu1 + lambda2) * x1;
}

double GOMarkovOperator18::func2(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    Q_UNUSED(x1);
    Q_UNUSED(lambda2);
    Q_UNUSED(mu2);
    return lambdaB1() * x0 - mu1 * x3 - (mu1 + lambda1) * x2;
}

double GOMarkovOperator18::func3(double t, double x0, double x1, double x2, double x3, double lambda1, double lambda2, double mu1, double mu2)
{
    Q_UNUSED(t);
    Q_UNUSED(x0);
    return lambda2 * x1 - lambda1 * x2 - (mu1 + mu2) * x3;
}
