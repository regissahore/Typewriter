#include <QObject>
#include <QPainter>
#include <qmath.h>
#include "GoMarkovOperator11.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"
#include "Messager.h"
#include "MessageFactory.h"
#include "GoMarkovOperatorFactory.h"

GoMarkovOperator11::GoMarkovOperator11() : GoMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->setK(1);
}

GoMarkovOperator11::~GoMarkovOperator11()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

int GoMarkovOperator11::K() const
{
    return this->_K;
}

int GoMarkovOperator11::I() const
{
    return this->_I;
}

int GoMarkovOperator11::L() const
{
    return this->_L;
}

int GoMarkovOperator11::J() const
{
    return this->_J;
}

void GoMarkovOperator11::setK(int value)
{
    this->_K = value;
}

void GoMarkovOperator11::setI(int value)
{
    this->_I = value;
}

void GoMarkovOperator11::setL(int value)
{
    this->_L = value;
}

void GoMarkovOperator11::setJ(int value)
{
    this->_J = value;
}

void GoMarkovOperator11::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    int inputNum = this->input()->number();
    QVector<DoubleVector> input;
    for (int i = 0; i < inputNum; ++i)
    {
        GoMarkovStatus* prevStatus = this->getPrevMarkovStatus(i);
        input.push_back(prevStatus->probabilityNormal());
    }
    DoubleVector PR = 0.0;
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
            DoubleVector temp = 1.0;
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
    DoubleVector lambda = this->getPrevMarkovStatus()->frequencyBreakdown();
    DoubleVector mu = this->getPrevMarkovStatus()->frequencyRepair();
    QVector<DoubleVector> a;
    QVector<DoubleVector> b;
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
    QVector<DoubleVector> p;
    p.push_back(1.0);
    for (int i = 1; i <= I + 1; ++i)
    {
        p.push_back(p[i - 1] * a[i] / b[i]);
    }
    DoubleVector sum1 = 0.0;
    DoubleVector sum2 = 0.0;
    for (int i = 0; i <= M - K; ++i)
    {
        sum1 = sum1 + p[i];
    }
    for (int i = M - K + 1; i <= I; ++i)
    {
        sum2 = sum2 + p[i];
    }
    DoubleVector lambdaR = p[M - K] * a[M - K + 1] / sum1;
    DoubleVector muR = p[M - K + 1] * b[M - K + 1] / sum2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator11::calcCommonOutputMarkovStatus(QVector<DoubleVector> PR)
{
    int I = this->I();
    int L = this->L();
    int J = this->J();
    int M = this->input()->number();
    int K = this->K();
    DoubleVector lambda = this->getPrevMarkovStatus()->frequencyBreakdown();
    DoubleVector mu = this->getPrevMarkovStatus()->frequencyRepair();
    QVector<DoubleVector> a;
    QVector<DoubleVector> b;
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
    QVector<DoubleVector> p;
    p.push_back(1.0);
    for (int i = 1; i <= I + 1; ++i)
    {
        p.push_back(p[i - 1] * a[i] / b[i]);
    }
    DoubleVector sum1 = 0.0;
    DoubleVector sum2 = 0.0;
    for (int i = 0; i <= M - K; ++i)
    {
        sum1 = sum1 + p[i];
    }
    for (int i = M - K + 1; i <= I; ++i)
    {
        sum2 = sum2 + p[i];
    }
    DoubleVector lambdaR = p[M - K] * a[M - K + 1] / sum1;
    DoubleVector muR = p[M - K + 1] * b[M - K + 1] / sum2;
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR[0]);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

DoubleVector GoMarkovOperator11::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    int inputNum = this->input()->number();
    DoubleVector PR = 0.0;
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
            DoubleVector temp = 1.0;
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

bool GoMarkovOperator11::errorDetect()
{
    if (this->GoMarkovOperator::errorDetect())
    {
        return true;
    }
    GoMarkovStatus *status1 = this->getPrevOperator(0)->markovStatus1();
    for (int i = 1; i < this->input()->number(); ++i)
    {
        GoMarkovStatus *status2 = this->getPrevOperator(i)->markovStatus1();
        if (fabs(status1->frequencyBreakdown().getValue(0) - status2->frequencyBreakdown().getValue(0)) > 1e-6)
        {
            this->_error = QObject::tr("Error: Operator ") + GoMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 's input should have same breakdown rate.").arg(this->id());
            return true;
        }
        if (fabs(status1->frequencyRepair().getValue(0) - status2->frequencyRepair().getValue(0)) > 1e-6)
        {
            this->_error = QObject::tr("Error: Operator ") + GoMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 's input should have same repair rate.").arg(this->id());
            return true;
        }
    }
    return false;
}

void GoMarkovOperator11::paintParameter(QPainter *painter)
{
    int y = 40;
    painter->drawText(-50, y, QObject::tr("K: %1").arg(this->K()));
    painter->drawText(-50, y + 20, QObject::tr("I: %1").arg(this->I()));
    painter->drawText(-50, y + 40, QObject::tr("J: %1").arg(this->J()));
    painter->drawText(-50, y + 60, QObject::tr("L: %1").arg(this->L()));
}

GoMarkovOperator* GoMarkovOperator11::copy()
{
    GoMarkovOperator11 *op = (GoMarkovOperator11*)this->GoMarkovOperator::copy();
    op->setK(this->K());
    op->setI(this->I());
    op->setL(this->L());
    op->setJ(this->J());
    return op;
}

void GoMarkovOperator11::save(QDomDocument &document, QDomElement &root)
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
    element.setAttribute("K", this->K());
    element.setAttribute("I", this->I());
    element.setAttribute("L", this->L());
    element.setAttribute("J", this->J());
    root.appendChild(element);
    this->status()->save(document, element);
    this->markovStatus()->save(document, element);
    this->markovStatus1()->save(document, element);
    this->markovStatus2()->save(document, element);
    this->markovStatus3()->save(document, element);
    this->markovStatus4()->save(document, element);
}

bool GoMarkovOperator11::tryOpen(QDomElement &root)
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
