#include <qmath.h>
#include "GoMarkovOperator2.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator2::GoMarkovOperator2() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GoMarkovOperator2::~GoMarkovOperator2()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

int GoMarkovOperator2::stopWorkNum() const
{
    return this->_stopWorkNum;
}

void GoMarkovOperator2::setStopWorkNum(int value)
{
    this->_stopWorkNum = value;
}

void GoMarkovOperator2::calcQualitativeProbability()
{
    int stopCount = 0;
    DoubleVector IS = 1.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        DoubleVector ISi = this->getPrevQualitativeStatus(i);
        IS = IS * (1.0 - ISi);
        if (ISi < 0.01)
        {
            ++stopCount;
        }
    }
    this->_qualitativeOutput[0] = 1.0 - IS;
    if (this->isBreakdownCorrelate() && stopCount >= this->stopWorkNum())
    {
        this->_qualitativeOutput[0] = 0.0;
    }
}

void GoMarkovOperator2::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    DoubleVector QR = 1.0;
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector PR = 1.0 - QR;
    DoubleVector lambdaR = miuR * QR / PR;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

void GoMarkovOperator2::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    DoubleVector QR = 1.0 - PR[0];
    DoubleVector miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        DoubleVector QSi = prevStatus->probabilityBreakdown();
        DoubleVector miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    DoubleVector lambdaR = miuR * QR / PR[0];
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}

DoubleVector GoMarkovOperator2::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    DoubleVector QR = 1.0;
    for (int i = 0; i < input.size(); ++i)
    {
        QR *= 1.0 - input[i];
    }
    return 1.0 - QR;
}

GoMarkovOperator* GoMarkovOperator2::copy()
{
    GoMarkovOperator2* op = (GoMarkovOperator2*)this->GoMarkovOperator::copy();
    op->setBreakdownNum(this->breakdownNum());
    return op;
}

void GoMarkovOperator2::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("stop_work_num", this->stopWorkNum());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GoMarkovOperator2::tryOpen(QDomElement &root)
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
    this->setStopWorkNum(root.attribute("stop_work_num", "1").toInt());
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
    return true;
}
