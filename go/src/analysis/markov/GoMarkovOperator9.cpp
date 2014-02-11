#include <algorithm>
#include <qmath.h>
#include "GoMarkovOperator9.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "RungeKuttaBreakdown2.h"
#include "RungeKuttaBreakdown3.h"
#include "RungeKuttaBreakdown4.h"
using namespace std;

GoMarkovOperator9::GoMarkovOperator9() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->_feedbackNum = 1;
    this->_feedbackStatus = new GoMarkovStatus();
    this->_feedbackStatus1 = new GoMarkovStatus();
    this->_feedbackStatus2 = new GoMarkovStatus();
    this->_feedbackStatus3 = new GoMarkovStatus();
    this->_feedbackStatus4 = new GoMarkovStatus();
    this->_rkFeedback2 = new RungeKuttaBreakdown2();
    this->_rkFeedback3 = new RungeKuttaBreakdown3();
    this->_rkFeedback4 = new RungeKuttaBreakdown4();
}

GoMarkovOperator9::~GoMarkovOperator9()
{
    this->GoMarkovOperator::~GoMarkovOperator();
    delete this->_feedbackStatus;
}

int GoMarkovOperator9::feedbackNum() const
{
    return this->_feedbackNum;
}

void GoMarkovOperator9::setFeedbackNum(int value)
{
    this->_feedbackNum = value;
}

GoMarkovOperator* GoMarkovOperator9::copy()
{
    GoMarkovOperator9 *op = (GoMarkovOperator9*)this->GoMarkovOperator::copy();
    op->setFeedbackNum(this->feedbackNum());
    op->feedbackStatus()->setProbabilityNormal(this->feedbackStatus()->probabilityNormal());
    op->feedbackStatus()->setFrequencyBreakdown(this->feedbackStatus()->frequencyBreakdown());
    op->feedbackStatus()->setFrequencyRepair(this->feedbackStatus()->frequencyRepair());
    op->feedbackStatus1()->setProbabilityNormal(this->feedbackStatus1()->probabilityNormal());
    op->feedbackStatus1()->setFrequencyBreakdown(this->feedbackStatus1()->frequencyBreakdown());
    op->feedbackStatus1()->setFrequencyRepair(this->feedbackStatus1()->frequencyRepair());
    op->feedbackStatus2()->setProbabilityNormal(this->feedbackStatus2()->probabilityNormal());
    op->feedbackStatus2()->setFrequencyBreakdown(this->feedbackStatus2()->frequencyBreakdown());
    op->feedbackStatus2()->setFrequencyRepair(this->feedbackStatus2()->frequencyRepair());
    op->feedbackStatus3()->setProbabilityNormal(this->feedbackStatus3()->probabilityNormal());
    op->feedbackStatus3()->setFrequencyBreakdown(this->feedbackStatus3()->frequencyBreakdown());
    op->feedbackStatus3()->setFrequencyRepair(this->feedbackStatus3()->frequencyRepair());
    op->feedbackStatus4()->setProbabilityNormal(this->feedbackStatus4()->probabilityNormal());
    op->feedbackStatus4()->setFrequencyBreakdown(this->feedbackStatus4()->frequencyBreakdown());
    op->feedbackStatus4()->setFrequencyRepair(this->feedbackStatus4()->frequencyRepair());
    return op;
}

GoMarkovStatus*  GoMarkovOperator9::feedbackStatus() const
{
    return this->_feedbackStatus;
}

GoMarkovStatus* GoMarkovOperator9::feedbackStatus1() const
{
    return this->_feedbackStatus1;
}

GoMarkovStatus* GoMarkovOperator9::feedbackStatus2() const
{
    return this->_feedbackStatus2;
}

GoMarkovStatus* GoMarkovOperator9::feedbackStatus3() const
{
    return this->_feedbackStatus3;
}

GoMarkovStatus* GoMarkovOperator9::feedbackStatus4() const
{
    return this->_feedbackStatus4;
}

void GoMarkovOperator9::initMarkovStatus(double time, double c12)
{
    this->GoMarkovOperator::initMarkovStatus(time, c12);
    if (1 == this->feedbackNum())
    {
        DoubleVector lambda = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector mu = this->feedbackStatus1()->frequencyRepair();
        DoubleVector PC = mu / (lambda + mu) * (1.0 + lambda / mu * DoubleVector::Exp(- (lambda + mu) * time)) + c12;
        this->feedbackStatus()->setProbabilityNormal(PC);
        this->feedbackStatus()->setFrequencyBreakdown(lambda);
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (2 == this->feedbackNum())
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown2->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->feedbackStatus()->setProbabilityNormal(P0);
        this->feedbackStatus()->setFrequencyBreakdown(lambda);
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (3 == this->feedbackNum())
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->feedbackStatus3()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown3->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2 + lambda3;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->feedbackStatus()->setProbabilityNormal(P0);
        this->feedbackStatus()->setFrequencyBreakdown(lambda);
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (4 == this->feedbackNum())
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->feedbackStatus3()->frequencyBreakdown();
        DoubleVector lambda4 = this->feedbackStatus4()->frequencyBreakdown();
        DoubleVector P0 = this->_rkBreakdown4->getY(0) + c12;
        DoubleVector lambda = lambda1 + lambda2 + lambda3 + lambda4;
        DoubleVector mu = lambda * P0 / (1.0 - P0);
        this->feedbackStatus()->setProbabilityNormal(P0);
        this->feedbackStatus()->setFrequencyBreakdown(lambda);
        this->feedbackStatus()->setFrequencyRepair(mu);
    }

    if (this->breakdownNum() == 1)
    {
        DoubleVector lambda1 = this->markovStatus1()->frequencyBreakdown();
        DoubleVector mu1 = this->markovStatus1()->frequencyRepair();
        DoubleVector Pinf = lambda1 / (lambda1 + mu1);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->markovStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (this->breakdownNum() == 2)
    {
        DoubleVector Pinf = this->_rkBreakdown2->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->markovStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (this->breakdownNum() == 3)
    {
        DoubleVector Pinf = this->_rkBreakdown3->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->markovStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->markovStatus()->setFrequencyRepair(mu);
    }
    else if (this->breakdownNum() == 4)
    {
        DoubleVector Pinf = this->_rkBreakdown4->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->markovStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->markovStatus()->setFrequencyRepair(mu);
    }

    if (this->feedbackNum() == 1)
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector mu1 = this->feedbackStatus1()->frequencyRepair();
        DoubleVector Pinf = lambda1 / (lambda1 + mu1);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->feedbackStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (this->feedbackNum() == 2)
    {
        DoubleVector Pinf = this->_rkFeedback2->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->feedbackStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (this->feedbackNum() == 3)
    {
        DoubleVector Pinf = this->_rkFeedback3->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->feedbackStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
    else if (this->feedbackNum() == 4)
    {
        DoubleVector Pinf = this->_rkFeedback4->getInf(0);
        DoubleVector Qinf = 1.0 - Pinf;
        DoubleVector lambda = this->feedbackStatus()->frequencyBreakdown();
        DoubleVector mu = lambda * Pinf / Qinf;
        this->feedbackStatus()->setFrequencyRepair(mu);
    }
}

void GoMarkovOperator9::initCalculation(double interval)
{
    this->GoMarkovOperator::initCalculation(interval);
    if (this->feedbackNum() == 2)
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector mu1 = this->feedbackStatus1()->frequencyRepair();
        DoubleVector mu2 = this->feedbackStatus2()->frequencyRepair();
        this->_rkFeedback2->setX(0.0);
        this->_rkFeedback2->setY(0, 1.0);
        this->_rkFeedback2->setLambda(lambda1.getValue(0), lambda2.getValue(0));
        this->_rkFeedback2->setMu(mu1.getValue(0), mu2.getValue(0));
        for (int i = 1; i < 3; ++i)
        {
            this->_rkFeedback2->setY(i, 0.0);
        }
        this->_rkFeedback2->setH(interval);
    }
    else if (this->feedbackNum() == 3)
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->feedbackStatus3()->frequencyBreakdown();
        DoubleVector mu1 = this->feedbackStatus1()->frequencyRepair();
        DoubleVector mu2 = this->feedbackStatus2()->frequencyRepair();
        DoubleVector mu3 = this->feedbackStatus3()->frequencyRepair();
        this->_rkFeedback3->setX(0.0);
        this->_rkFeedback3->setY(0, 1.0);
        this->_rkFeedback3->setLambda(lambda1.getValue(0), lambda2.getValue(0), lambda3.getValue(0));
        this->_rkFeedback3->setMu(mu1.getValue(0), mu2.getValue(0), mu3.getValue(0));
        for (int i = 1; i < 4; ++i)
        {
            this->_rkFeedback3->setY(i, 0.0);
        }
        this->_rkFeedback3->setH(interval);
    }
    else if (this->feedbackNum() == 4)
    {
        DoubleVector lambda1 = this->feedbackStatus1()->frequencyBreakdown();
        DoubleVector lambda2 = this->feedbackStatus2()->frequencyBreakdown();
        DoubleVector lambda3 = this->feedbackStatus3()->frequencyBreakdown();
        DoubleVector lambda4 = this->feedbackStatus4()->frequencyBreakdown();
        DoubleVector mu1 = this->feedbackStatus1()->frequencyRepair();
        DoubleVector mu2 = this->feedbackStatus2()->frequencyRepair();
        DoubleVector mu3 = this->feedbackStatus3()->frequencyRepair();
        DoubleVector mu4 = this->feedbackStatus4()->frequencyRepair();
        this->_rkFeedback4->setLambda(lambda1.getValue(0), lambda2.getValue(0), lambda3.getValue(0), lambda4.getValue(0));
        this->_rkFeedback4->setMu(mu1.getValue(0), mu2.getValue(0), mu3.getValue(0), mu4.getValue(0));
        this->_rkFeedback4->setX(0.0);
        this->_rkFeedback4->setY(0, 1.0);
        for (int i = 1; i < 5; ++i)
        {
            this->_rkFeedback4->setY(i, 0.0);
        }
        this->_rkFeedback4->setH(interval);
    }

    if (this->breakdownNum() == 2)
    {
        this->_rkBreakdown2->calculateInfinity();
    }
    else if (this->breakdownNum() == 3)
    {
        this->_rkBreakdown3->calculateInfinity();
    }
    else if (this->breakdownNum() == 4)
    {
        this->_rkBreakdown4->calculateInfinity();
    }

    if (this->feedbackNum() == 2)
    {
        this->_rkFeedback2->calculateInfinity();
    }
    else if (this->feedbackNum() == 3)
    {
        this->_rkFeedback3->calculateInfinity();
    }
    else if (this->feedbackNum() == 4)
    {
        this->_rkFeedback4->calculateInfinity();
    }

    this->_lambdaS1Sum = 0.0;
    this->_muS1Sum = 0.0;
    this->_sumCount1 = 0;
    this->_currentCount = 0;
}

void GoMarkovOperator9::prepareNextCalculation(int count, double time)
{
    this->GoMarkovOperator::prepareNextCalculation(count, time);
    if (this->feedbackNum() == 2)
    {
        this->_rkFeedback2->nextStep();
    }
    if (this->feedbackNum() == 3)
    {
        this->_rkFeedback3->nextStep();
    }
    else if (this->feedbackNum() == 4)
    {
        this->_rkFeedback4->nextStep();
    }
    this->_currentCount = count;
}

void GoMarkovOperator9::prepareSum()
{
    if (this->_currentCount > this->_sumCount1)
    {
        DoubleVector lambdaS1 = this->getPrevMarkovStatus(0)->frequencyBreakdown();
        DoubleVector muS1 = this->getPrevMarkovStatus(0)->frequencyRepair();
        if (std::isinf(lambdaS1.getValue(0)) || std::isnan(lambdaS1.getValue(0)))
        {
            this->_lambdaS1Sum = this->_lambdaS1Sum + this->lambdaS1;
        }
        else
        {
            this->_lambdaS1Sum = this->_lambdaS1Sum + lambdaS1;
            this->lambdaS1 = this->_lambdaS1Sum / this->_currentCount;
        }
        if (std::isinf(muS1.getValue(0)) || std::isnan(muS1.getValue(0)))
        {
            this->_muS1Sum = this->_muS1Sum + this->muS1;
        }
        else
        {
            this->_muS1Sum = this->_muS1Sum + muS1;
            this->muS1 = this->_muS1Sum / this->_currentCount;
        }
        ++this->_sumCount1;
        FILE *file = fopen("test.txt", "a");
        fprintf(file, "\n\n9A Count %d\n", this->_currentCount);
        fprintf(file, "\tS1: %lf %lf\n", lambdaS1.getValue(0), muS1.getValue(0));
        fprintf(file, "\tSum: %lf %lf\n", _lambdaS1Sum.getValue(0), _muS1Sum.getValue(0));
        fprintf(file, "\tAvr: %lf %lf\n", this->lambdaS1.getValue(0), this->muS1.getValue(0));
        fclose(file);
    }
}

void GoMarkovOperator9::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("real", this->realID());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("dual", this->breakdownNum());
    element.setAttribute("breakdown", this->isBreakdownCorrelate());
    element.setAttribute("global_feedback", this->isGlobalFeedback());
    element.setAttribute("name", this->name());
    element.setAttribute("feedback", this->feedbackNum());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
    this->feedbackStatus()->save(document, element);
    this->feedbackStatus1()->save(document, element);
    this->feedbackStatus2()->save(document, element);
    this->feedbackStatus3()->save(document, element);
    this->feedbackStatus4()->save(document, element);
}

bool GoMarkovOperator9::tryOpen(QDomElement &root)
{
    if (root.tagName() != "model")
    {
        return false;
    }
    this->setType(root.attribute("type").toInt());
    this->setId(root.attribute("id").toInt());
    if (root.hasAttribute("real"))
    {
        this->setRealID(root.attribute("real").toInt());
    }
    else
    {
        this->setRealID(root.attribute("id").toInt());
    }
    this->input()->setNumber(root.attribute("input").toInt());
    this->subInput()->setNumber(root.attribute("subInput").toInt());
    this->output()->setNumber(root.attribute("output").toInt());
    this->setBreakdownNum(root.attribute("dual").toInt());
    this->setBreakdownCorrelate(root.attribute("breakdown").toInt());
    this->setIsGlobalFeedback(root.attribute("global_feedback", "0").toInt());
    this->setName(root.attribute("name", ""));
    this->setFeedbackNum(root.attribute("feedback", "1").toInt());
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
    element = element.nextSiblingElement();
    if (!this->markovStatus1()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus2()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus3()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->markovStatus4()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->feedbackStatus()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->feedbackStatus1()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->feedbackStatus2()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->feedbackStatus3()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->feedbackStatus4()->tryOpen(element))
    {
        return false;
    }
    return true;
}
