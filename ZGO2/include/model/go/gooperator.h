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

class GOIOModel;
class GOStatus;

class GOOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GOOperator();
    GOIOModel* input() const;
    GOIOModel* subInput() const;
    GOIOModel* output() const;
    GOStatus* status() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOIOModel *_input; /** Main input. */
    GOIOModel *_subInput; /** Sub input. */
    GOIOModel *_output; /** Output. */
    GOStatus *_status;

};

#endif // GOOPERATOR_H
