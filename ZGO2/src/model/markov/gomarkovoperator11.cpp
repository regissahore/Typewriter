#include <qmath.h>
#include "gomarkovoperator11.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator11::GOMarkovOperator11() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setK(1);
}

GOMarkovOperator11::~GOMarkovOperator11()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

int GOMarkovOperator11::K() const
{
    return this->_K;
}

void GOMarkovOperator11::setK(int value)
{
    this->_K = value;
}

void GOMarkovOperator11::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    int inputNum = this->input()->number();
    QVector<double> input;
    for (int i = 0; i < inputNum; ++i)
    {
        GOMarkovStatus* prevStatus = this->getPrevMarkovStatus(i);
        input.push_back(prevStatus->probabilityNormal());
    }
    double PR = 0.0;
    for (int i = 0; i < (1 << inputNum); ++i)
    {
        int successNum = 0;
        for (int j = 0; j < inputNum; ++j)
        {
            if (i & (1 << j))
            {
                ++successNum;
            }
        }
        if (successNum >= this->K())
        {
            double temp = 1.0;
            for (int j = 0; j < inputNum; ++j)
            {
                if (i & (1 << j))
                {
                    temp *= input[j];
                }
                else
                {
                    temp *= (1.0 - input[j]);
                }
            }
            PR += temp;
        }
    }
    //double QR = 1.0 - PR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
}

void GOMarkovOperator11::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    Q_UNUSED(PR);
}

double GOMarkovOperator11::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(input);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    return 0.0;
}

void GOMarkovOperator11::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("model");
    element.setAttribute("type", this->type());
    element.setAttribute("id", this->id());
    element.setAttribute("input", this->input()->number());
    element.setAttribute("subInput", this->subInput()->number());
    element.setAttribute("output", this->output()->number());
    element.setAttribute("K", this->K());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
}

bool GOMarkovOperator11::tryOpen(QDomElement &root)
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
    this->setK(root.attribute("K").toInt());
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
    return true;
}
