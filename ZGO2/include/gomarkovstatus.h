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
    void setProbabilityNormal(DoubleVector value);
    void setProbabilityBreakdown(DoubleVector value);
    void setFrequencyBreakdown(DoubleVector value);
    void setFrequencyRepair(DoubleVector value);
    void setRepairTime(DoubleVector value);
    GOMarkovStatus* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    DoubleVector _probabilityNormal;
    DoubleVector _frequencyBreakdown;
    DoubleVector _frequencyRepair;
};

#endif // GOMARKOVSTATUS_H
