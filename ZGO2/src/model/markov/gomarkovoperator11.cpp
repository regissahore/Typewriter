#include <QObject>
#include <qmath.h>
#include "gomarkovoperator11.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

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

int GOMarkovOperator11::I() const
{
    return this->_I;
}

int GOMarkovOperator11::L() const
{
    return this->_L;
}

int GOMarkovOperator11::J() const
{
    return this->_J;
}

void GOMarkovOperator11::setK(int value)
{
    this->_K = value;
}

void GOMarkovOperator11::setI(int value)
{
    this->_I = value;
}

void GOMarkovOperator11::setL(int value)
{
    this->_L = value;
}

void GOMarkovOperator11::setJ(int value)
{
    this->_J = value;
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

    int I = this->I();
    int L = this->L();
    int J = this->J();
    int M = this->input()->number();
    int K = this->K();
    double lambda = this->getPrevMarkovStatus()->frequencyBreakdown();
    double mu = this->getPrevMarkovStatus()->frequencyRepair();
    QVector<double> a;
    QVector<double> b;
    a.push_back(0.0);
    b.push_back(1.0);
    int maxIndex = M - K;
    if (I > maxIndex)
    {
        maxIndex = I;
    }
    for (int i = 0; i <= I;)
    {
        ++i;
        if (J == 0 || M - i + 1 < K)
        {
            a.push_back((M - i + 1) * lambda);
        }
        else
        {
            a.push_back(K * lambda);
        }
        if (i <= L)
        {
            b.push_back(i * mu);
        }
        else
        {
            b.push_back(L * mu);
        }
    }
    QVector<double> p;
    p.push_back(1.0);
    for (int i = 1; i <= I + 1; ++i)
    {
        p.push_back(p[i - 1] * a[i] / b[i]);
    }
    double sum1 = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i <= M - K; ++i)
    {
        sum1 = sum1 + p[i];
    }
    for (int i = M - K + 1; i <= I; ++i)
    {
        sum2 = sum2 + p[i];
    }
    double lambdaR = p[M - K] * a[M - K + 1] / sum1;
    double muR = p[M - K + 1] * b[M - K + 1] / sum2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GOMarkovOperator11::calcCommonOutputMarkovStatus(QVector<double> PR)
{
    int I = this->I();
    int L = this->L();
    int J = this->J();
    int M = this->input()->number();
    int K = this->K();
    double lambda = this->getPrevMarkovStatus()->frequencyBreakdown();
    double mu = this->getPrevMarkovStatus()->frequencyRepair();
    QVector<double> a;
    QVector<double> b;
    a.push_back(0.0);
    b.push_back(1.0);
    int maxIndex = M - K;
    if (I > maxIndex)
    {
        maxIndex = I;
    }
    for (int i = 0; i <= I;)
    {
        ++i;
        if (J == 0 || M - i + 1 < K)
        {
            a.push_back((M - i + 1) * lambda);
        }
        else
        {
            a.push_back(K * lambda);
        }
        if (i <= L)
        {
            b.push_back(i * mu);
        }
        else
        {
            b.push_back(L * mu);
        }
    }
    QVector<double> p;
    p.push_back(1.0);
    for (int i = 1; i <= I + 1; ++i)
    {
        p.push_back(p[i - 1] * a[i] / b[i]);
    }
    double sum1 = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i <= M - K; ++i)
    {
        sum1 = sum1 + p[i];
    }
    for (int i = M - K + 1; i <= I; ++i)
    {
        sum2 = sum2 + p[i];
    }
    double lambdaR = p[M - K] * a[M - K + 1] / sum1;
    double muR = p[M - K + 1] * b[M - K + 1] / sum2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

double GOMarkovOperator11::calcTempOutputMarkovStatus(double time, QVector<double> input, QVector<double> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    int inputNum = this->input()->number();
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
    return PR;
}

bool GOMarkovOperator11::errorDetect(Messager *messager)
{
    if (this->GOMarkovOperator::errorDetect(messager))
    {
        return true;
    }
    GOMarkovStatus *status1 = this->getPrevMarkovStatus(0);
    for (int i = 1; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *status2 = this->getPrevMarkovStatus(i);
        if (fabs(status1->frequencyBreakdown() - status2->frequencyBreakdown()) > 1e-6)
        {
            Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
            message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 's input should have same breakdown rate.").arg(this->id());
            messager->sendMessage(message);
            return true;
        }
        if (fabs(status1->frequencyRepair() - status2->frequencyRepair()) > 1e-6)
        {
            Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
            message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 's input should have same repair rate.").arg(this->id());
            messager->sendMessage(message);
            return true;
        }
    }
    return false;
}

GOMarkovOperator* GOMarkovOperator11::copy()
{
    GOMarkovOperator11 *op = new GOMarkovOperator11();
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

    op->setK(this->K());
    op->setI(this->I());
    op->setL(this->L());
    op->setJ(this->J());
    return op;
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
    element.setAttribute("I", this->I());
    element.setAttribute("L", this->L());
    element.setAttribute("J", this->J());
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
    this->setI(root.attribute("I").toInt());
    this->setL(root.attribute("L").toInt());
    this->setJ(root.attribute("J").toInt());
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
