#ifndef GOMARKOVSTATUS_H
#define GOMARKOVSTATUS_H
/**
 * The status of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "domitem.h"
#include "doublevector.h"

class QString;

class GOMarkovStatus : public DomItem
{
public:
    GOMarkovStatus();
    virtual ~GOMarkovStatus();

    DoubleVector probabilityNormal() const;
    DoubleVector probabilityBreakdown() const;
    DoubleVector frequencyBreakdown() const;
    DoubleVector frequencyRepair() const;
    DoubleVector repairTime() const;

    void setProbabilityNormal(const DoubleVector &value);
    void setProbabilityBreakdown(const DoubleVector &value);
    void setFrequencyBreakdown(const DoubleVector &value);
    void setFrequencyRepair(const DoubleVector &value);
    void setRepairTime(const DoubleVector &value);

    void setProbabilityNormal(const int pos, const double value);
    void setProbabilityBreakdown(const int pos, const double value);
    void setFrequencyBreakdown(const int pos, const double value);
    void setFrequencyRepair(const int pos, const double value);
    void setRepairTime(const int pos, const double value);

    void setVectorLength(const int len);

    GOMarkovStatus* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    DoubleVector _probabilityNormal;
    DoubleVector _frequencyBreakdown;
    DoubleVector _frequencyRepair;
};

#endif // GOMARKOVSTATUS_H
