#ifndef GOSTATUS_H
#define GOSTATUS_H
#include "stable.h"
#include "DomItem.h"

class GoStatus : public DomItem
{
public:
    GoStatus();
    virtual ~GoStatus();
    int number() const;
    void setNumber(int number);
    double probability(int index) const;
    void setProbability(int index, double value);
    QString description(int index) const;
    void setDescription(int index, const QString value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<double> _probability;
    QVector<QString> _description;
};

#endif // GOSTATUS_H
