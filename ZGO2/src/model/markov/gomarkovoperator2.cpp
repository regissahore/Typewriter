#include <qmath.h>
#include "gomarkovoperator2.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gosignal.h"
#include "goparameter.h"
#include "gomarkovstatus.h"

GOMarkovOperator2::GOMarkovOperator2() : GOMarkovOperator()
{
    this->input()->setNumber(3);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
}

GOMarkovOperator2::~GOMarkovOperator2()
{
    this->GOMarkovOperator::~GOMarkovOperator();
}

void GOMarkovOperator2::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    double QR = 1.0;
    double miuR = 0.0;
    for (int i = 0; i < this->input()->number(); ++i)
    {
        GOMarkovStatus *prevStatus = this->getPrevMarkovStatus(i);
        double QSi = prevStatus->probabilityBreakdown();
        double miuSi = prevStatus->frequencyRepair();
        QR *= QSi;
        miuR += miuSi;
    }
    double PR = 1 - QR;
    double lambdaR = miuR * QR / PR;
    this->initOutputMarkovStatus();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(miuR);
}
