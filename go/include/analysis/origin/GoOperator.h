#ifndef GOOPERATOR_H
#define GOOPERATOR_H
#include <QVector>
#include "IdentifiedItem.h"
#include "TypedItem.h"
#include "DomItem.h"

class GoInput;
class GoOutput;
class GoStatus;
class GoAccumulative;
class GoParameter;

class GoOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GoOperator();
    virtual ~GoOperator();
    int realID() const;
    void setRealID(const int value);
    GoInput* input() const;
    GoInput* subInput() const;
    GoOutput* output() const;
    GoStatus *status() const;
    QVector<GoAccumulative*>* accmulatives() const;
    GoParameter *parameter() const;
    QString name() const;
    void setName(const QString name);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    int _realID;
    GoInput *_input;
    GoInput *_subInput;
    GoOutput *_output;
    GoStatus  *_status;
    QVector<GoAccumulative*> *_accumulatives;
    GoParameter *_parameter;
    QString _name;
};

#endif // GOOPERATOR_H
