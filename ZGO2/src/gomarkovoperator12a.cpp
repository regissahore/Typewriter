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
    GOMarkovOperator *prevOperator = this->getPrevOperator();
    for (int i = 0; i < this->output()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = prevOperator->markovOutputStatus()->at(i);
        DoubleVector PR = prevStatus->probabilityNormal();
        DoubleVector lambdaR = prevStatus->frequencyBreakdown();
        DoubleVector muR = prevStatus->frequencyRepair();
        this->markovOutputStatus()->at(i)->setProbabilityNormal(PR);
        this->markovOutputStatus()->at(i)->setFrequencyBreakdown(lambdaR);
        this->markovOutputStatus()->at(i)->setFrequencyRepair(muR);
    }
}

DoubleVector GOMarkovOperator12A::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    return input[index];
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
