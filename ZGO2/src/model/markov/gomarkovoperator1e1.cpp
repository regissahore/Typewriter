#include <cstdio>
#include <qmath.h>
#include "gomarkovoperator1e1.h"
#include "gomarkovstatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "goparameter.h"

GOMarkovOperator1E1::GOMarkovOperator1E1() : GOMarkovOperator()
{
    this->_markovStatus2 = new GOMarkovStatus();
}

GOMarkovOperator1E1::~GOMarkovOperator1E1()
{
    this->GOMarkovOperator::~GOMarkovOperator();
    delete this->_markovStatus2;
}

GOMarkovStatus* GOMarkovOperator1E1::markovStatus2() const
{
    return this->_markovStatus2;
}

void GOMarkovOperator1E1::initMarkovStatus(double time)
{
    char s[100];
    double lamda1 = this->markovStatus()->frequencyBreakdown().toString().toDouble();
    double miu1 = this->markovStatus()->frequencyRepair().toString().toDouble();
    double lamda2 = this->markovStatus2()->frequencyBreakdown().toString().toDouble();
    double miu2 = this->markovStatus2()->frequencyRepair().toString().toDouble();
    double s1 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) + sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
    double s2 = 0.5 * (-(lamda1 + lamda2 + miu1 + miu2) - sqrt((lamda1 - lamda2 + miu1 - miu2) * (lamda1 - lamda2 + miu1 - miu2) + 4 * lamda1 * lamda2));
    double p1 = miu1 / s1 * miu2 / s2 +
            (s1 * s1 + (miu1 + miu2) * s1 + miu1 * miu2) / (s1 * (s1 - s2)) * exp(s1 * time) +
            (s2 * s2 + (miu1 + miu2) * s2 + miu1 * miu2) / (s2 * (s2 - s1)) * exp(s2 * time);
    if (p1 > 1.0)
    {
        p1 = 1.0;
    }
    double p2 = 1 - p1;
    sprintf(s, "%.6lf", p1);
    this->status()->setProbability(1, BigDecimal::valueOf(QString(s)));
    sprintf(s, "%.6lf", p2);
    this->status()->setProbability(2, BigDecimal::valueOf(QString(s)));
}

void GOMarkovOperator1E1::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->parameter()->save(document, element);
}

bool GOMarkovOperator1E1::tryOpen(QDomElement &root)
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
    if (!this->markovStatus2()->tryOpen(element))
    {
        return false;
    }
    element = element.nextSiblingElement();
    if (!this->parameter()->tryOpen(element))
    {
        return false;
    }
    return true;
}
