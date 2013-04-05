#ifndef GOMARKOVOPERATOR_H
#define GOMARKOVOPERATOR_H
/**
 * The operator model for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "identifieditem.h"
#include "typeditem.h"
#include "domitem.h"
#include "bigdecimal.h"

class GOInput;
class GOOutput;
class GOParameter;
class GOMarkovStatus;

class GOMarkovOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GOMarkovOperator();
    virtual ~GOMarkovOperator();
    GOInput* input() const;
    GOInput* subInput() const;
    GOOutput* output() const;
    GOMarkovStatus* status() const;
    QVector<GOMarkovStatus*>* outputStatus() const;
    GOParameter *parameter() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOInput *_input;
    GOInput *_subInput;
    GOOutput *_output;
    GOMarkovStatus *_status;
    QVector<GOMarkovStatus*> *_outputStatus;
    GOParameter *_parameter;
};

#endif // GOMARKOVOPERATOR_H
