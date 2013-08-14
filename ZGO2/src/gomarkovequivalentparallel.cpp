#include "gomarkovequivalentparallel.h"
#include "gomarkovstatus.h"
#include "gomarkovoperator.h"
#include "gomarkovoperatorfactory.h"
#include "goinput.h"
#include "goparameter.h"

GOMarkovEquivalentParallel::GOMarkovEquivalentParallel() : GOMarkovEquivalent()
{
}

GOMarkovStatus GOMarkovEquivalentParallel::getEquivalentStatus()
{
    int M, K = 0;
    int I = this->I();
    int L = this->L();
    int J = this->J();
    M = this->_operators->at(this->_operators->size() - 1)->input()->number();
    switch (this->_operators->at(this->_operators->size() - 1)->TypedItem::type())
    {
    case GOMarkovOperatorFactory::Operator_Type_2:
        K = 1;
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        K = M;
        break;
    case GOMarkovOperatorFactory::Operator_Type_11:
        K = this->_operators->at(this->_operators->size() - 1)->parameter()->parameter(0);
        break;
    }
    double lamda = this->_operators->at(0)->markovStatus1()->frequencyBreakdown();
    double miu = this->_operators->at(0)->markovStatus1()->frequencyRepair();
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
            a.push_back((M - i + 1) * lamda);
        }
        else
        {
            a.push_back(K * lamda);
        }
        if (i <= L)
        {
            b.push_back(i * miu);
        }
        else
        {
            b.push_back(L * miu);
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
    lamda = p[M - K] * a[M - K + 1] / sum1;
    miu = p[M - K + 1] * b[M - K + 1] / sum2;
    GOMarkovStatus status;
    status.setFrequencyBreakdown(lamda);
    status.setFrequencyRepair(miu);
    return status;
}

void GOMarkovEquivalentParallel::save(QDomDocument &document, QDomElement &root)
{
    QDomElement equivalentRoot = document.createElement("parallel");
    for (int i = 0; i < this->operators()->size(); ++i)
    {
        QDomElement element = document.createElement("operator");
        element.setAttribute("id", this->operators()->at(i)->realID());
        equivalentRoot.appendChild(element);
    }
    root.appendChild(equivalentRoot);
}

bool GOMarkovEquivalentParallel::tryOpen(QDomElement &root)
{
    if (root.tagName() != "parallel")
    {
        return false;
    }
    this->_idList->clear();
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        this->_idList->push_back(element.attribute("id").toInt());
    }
    return true;
}
