#ifndef GOMARKOVSTATUS_H
#define GOMARKOVSTATUS_H
/**
 * The status of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "bigdecimal.h"
#include "domitem.h"

class QString;

class GOMarkovStatus : public DomItem
{
public:
    GOMarkovStatus();
    virtual ~GOMarkovStatus();
    BigDecimal probabilityNormal() const;
    BigDecimal probabilityBreakdown() const;
    BigDecimal frequencyBreakdown() const;
    BigDecimal frequencyRepair() const;
    void setProbabilityNormal(QString value);
    void setProbabilityBreakdown(QString value);
    void setFrequencyBreakdown(QString value);
    void setFrequencyRepair(QString value);
    void setRepairTime(QString value);
    void setProbabilityNormal(BigDecimal value);
    void setProbabilityBreakdown(BigDecimal value);
    void setFrequencyBreakdown(BigDecimal value);
    void setFrequencyRepair(BigDecimal value);
    void setRepairTime(BigDecimal value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    BigDecimal _probabilityNormal;
    BigDecimal _probabilityBreakdown;
    BigDecimal _frequencyBreakdown;
    BigDecimal _frequencyRepair;
};

#endif // GOMARKOVSTATUS_H
