#ifndef GOOPERATOR_H
#define GOOPERATOR_H
/**
 * GO操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "identifieditem.h"
#include "goiomodel.h"
#include "nameditem.h"
#include "typeditem.h"
#include "domitem.h"

class GOOperator : public IdentifiedItem, public TypedItem, public DomItem
{
public:
    GOOperator();
    GOIOModel* input() const;
    GOIOModel* subInput() const;
    GOIOModel* output() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

private:
    GOIOModel *_input; /** 主输入的信号流。 */
    GOIOModel *_subInput; /** 次输入信号流。 */
    GOIOModel *_output; /** 输出的信号流。 */
};

#endif // GOOPERATOR_H
