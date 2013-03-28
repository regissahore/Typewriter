#ifndef GOSTATUS_H
#define GOSTATUS_H
/**
 * The status of the GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>
#include "domitem.h"

class GOStatus : public DomItem
{
public:
    GOStatus();
    int probablityNumber() const;
    void setProbabilityNumber(int number);
    float probability(int index) const;
    void setProbability(int index, const float value);
    int accumulativeNumber() const;
    void setAccumulativeNumber(int number);
    float accumulative(int index) const;
    void setAccumulative(int index, const float value);
    QString description(int index) const;
    void setDescription(int index, const QString value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<float> _probability;
    QVector<float> _accumulative; /** The accumulative probability. */
    QVector<QString> _description;
};

#endif // GOSTATUS_H
