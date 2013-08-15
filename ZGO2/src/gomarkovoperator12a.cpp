#include <QObject>
#include <qmath.h>
#include "gomarkovoperator12a.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"
#include "messager.h"
#include "messagefactory.h"
#include "gomarkovoperatorfactory.h"

GOMarkovOperator12A::GOMarkovOperator12A() : GOMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(3);
}

GOMarkovOperator12A::~GOMarkovOperator12A()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator12A::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GOMarkovStatus *prevStatus = this->getPrevMarkovStatus();
    DoubleVector PR = prevStatus->probabilityNormal();
    DoubleVector lambdaR = prevStatus->frequencyBreakdown();
    DoubleVector muR = prevStatus->frequencyRepair();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR.getValue(i));
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR.getValue(i));
    }
}

DoubleVector GOMarkovOperator12A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[0].getValue(index);
}

bool GOMarkovOperator12A::errorDetect(Messager *messager)
{
    if (this->GOMarkovOperator::errorDetect(messager))
    {
        return true;
    }
    GOMarkovOperator *op = this->getPrevOperator();
    if (!GOMarkovOperatorFactory::isVectorOutput(op->TypedItem::type()))
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The input should be a vector.").arg(this->id());
        messager->sendMessage(message);
        return true;
    }
    if (this->output()->number() != op->markovOutputStatus()->size())
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_OUTPUT_ERROR);
        message->paramString = QObject::tr("Error: Operator ") + GOMarkovOperatorFactory::typeName(this->TypedItem::type()) + QObject::tr("-%1 The number of output should matches the length of the input vector.").arg(this->id());
        messager->sendMessage(message);
        return true;
    }
    return false;
}
