#ifndef GOPARAMETER_H
#define GOPARAMETER_H
#include "stable.h"
#include "DomItem.h"

class GoParameter : public DomItem
{
public:
    GoParameter();
    virtual ~GoParameter();
    int number() const;
    void setNumber(int number);
    double parameter(const int index) const;
    void setParameter(const int index, const double value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    QVector<double> _parameter;
};

#endif // GOPARAMETER_H
