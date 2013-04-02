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

class GOOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GOOperator();
    virtual ~GOOperator();
    GOInput* input() const;
    GOInput* subInput() const;
    GOOutput* output() const;
    GOStatus *status() const;
    QVector<GOAccumulative*>* accmulatives() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOInput *_input;
    GOInput *_subInput;
    GOOutput *_output;
    GOStatus  *_status;
    QVector<GOAccumulative*> *_accumulatives;
};

#endif // GOOPERATOR_H
