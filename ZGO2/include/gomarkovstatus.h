#ifndef GOMARKOVSTATUS_H
#define GOMARKOVSTATUS_H
/**
 * The status of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "domitem.h"

class QString;

class GOMarkovStatus : public DomItem
{
public:
    GOMarkovStatus();
    virtual ~GOMarkovStatus();
    double probabilityNormal() const;
    double probabilityBreakdown() const;
    double frequencyBreakdown() const;
    double frequencyRepair() const;
    void setProbabilityNormal(QString value);
    void setProbabilityBreakdown(QString value);
    void setFrequencyBreakdown(QString value);
    void setFrequencyRepair(QString value);
    void setRepairTime(QString value);
    void setProbabilityNormal(double value);
    void setProbabilityBreakdown(double value);
    void setFrequencyBreakdown(double value);
    void setFrequencyRepair(double value);
    void setRepairTime(double value);
    GOMarkovStatus* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    double _probabilityNormal;
    double _probabilityBreakdown;
    double _frequencyBreakdown;
    double _frequencyRepair;
};

#endif // GOMARKOVSTATUS_H
