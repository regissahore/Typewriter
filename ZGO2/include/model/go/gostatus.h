#ifndef GOSTATUS_H
#define GOSTATUS_H
/**
 * The status of the GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>
#include "domitem.h"
#include "bigdecimal.h"

class GOStatus : public DomItem
{
public:
    GOStatus();
    int number() const;
    void setNumber(int number);
    BigDecimal probability(int index) const;
    void setProbability(int index, BigDecimal value);
    QString description(int index) const;
    void setDescription(int index, const QString value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<BigDecimal> _probability;
    QVector<QString> _description;
};

#endif // GOSTATUS_H
