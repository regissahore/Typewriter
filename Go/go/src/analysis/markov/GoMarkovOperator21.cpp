#include <qmath.h>
#include "GoMarkovOperator21.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoSignal.h"
#include "GoParameter.h"
#include "GoMarkovStatus.h"

GoMarkovOperator21::GoMarkovOperator21() : GoMarkovOperator()
{
    this->input()->setNumber(1);
    this->subInput()->setNumber(0);
    this->output()->setNumber(1);
    this->initOutputMarkovStatus();
    this->setIsGlobalFeedback(true);
}

GoMarkovOperator21::~GoMarkovOperator21()
{
    this->GoMarkovOperator::~GoMarkovOperator();
}

void GoMarkovOperator21::calcOutputMarkovStatus(double time)
{
    Q_UNUSED(time);
    GoMarkovStatus *status = this->getPrevMarkovStatus();
    DoubleVector PR = status->probabilityNormal();
    DoubleVector lambdaR = status->frequencyBreakdown();
    DoubleVector muR = status->frequencyRepair();
    this->markovOutputStatus()->at(0)->setProbabilityNormal(PR);
    this->markovOutputStatus()->at(0)->setFrequencyBreakdown(lambdaR);
    this->markovOutputStatus()->at(0)->setFrequencyRepair(muR);
}

void GoMarkovOperator21::calcQualitativeProbability()
{
    DoubleVector IC = this->qualitativeStatus();
    this->_qualitativeOutput[0] = IC;
}

DoubleVector GoMarkovOperator21::calcTempOutputMarkovStatus(double time, QVector<DoubleVector> input, QVector<DoubleVector> subInput, int index)
{
    Q_UNUSED(time);
    Q_UNUSED(subInput);
    Q_UNUSED(index);
    return input[0];
}

double GoMarkovOperator21::pathProbability() const
{
    return this->_pathProbability;
}

double GoMarkovOperator21::cutProbability() const
{
    return this->_cutProbability;
}

void GoMarkovOperator21::setPathProbability(double value)
{
    this->_pathProbability = value;
}

void GoMarkovOperator21::setCutProbability(double value)
{
    this->_cutProbability = value;
}

QVector<double>& GoMarkovOperator21::savedProbabilites()
{
    return this->_savedProbabilities;
}
