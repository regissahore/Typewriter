#ifndef GOOPERATOR_H
#define GOOPERATOR_H
/**
 * The GO operator model.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "identifieditem.h"
#include "typeditem.h"
#include "domitem.h"

class GOInput;
class GOOutput;
class GOStatus;
class GOAccumulative;
class GOParameter;

class GOOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GOOperator();
    virtual ~GOOperator();
    int realID() const;
    void setRealID(const int value);
    GOInput* input() const;
    GOInput* subInput() const;
    GOOutput* output() const;
    GOStatus *status() const;
    QVector<GOAccumulative*>* accmulatives() const;
    GOParameter *parameter() const;
    QString name() const;
    void setName(const QString name);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    int _realID;
    GOInput *_input;
    GOInput *_subInput;
    GOOutput *_output;
    GOStatus  *_status;
    QVector<GOAccumulative*> *_accumulatives;
    GOParameter *_parameter;
    QString _name;
};

#endif // GOOPERATOR_H
