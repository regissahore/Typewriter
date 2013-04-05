#ifndef GOPARAMETER_H
#define GOPARAMETER_H
/**
 * Save the extend parameters for GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "domitem.h"

class GOParameter : public DomItem
{
public:
    GOParameter();
    virtual ~GOParameter();
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
