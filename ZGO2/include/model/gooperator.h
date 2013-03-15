#ifndef GOOPERATOR_H
#define GOOPERATOR_H
/**
 * GO操作符。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "model/identifieditem.h"
#include "model/goiomodel.h"
#include "model/nameditem.h"

class GOOperator : public IdentifiedItem, public NamedItem
{
public:
    GOOperator();
    int type() const;
    void setType(const int type);
    GOIOModel* input() const;
    GOIOModel* subInput() const;
    GOIOModel* output() const;

private:
    int _type; /** 操作符的类型。 */
    GOIOModel *_input; /** 主输入的信号流。 */
    GOIOModel *_subInput; /** 次输入信号流。 */
    GOIOModel *_output; /** 输出的信号流。 */
};

#endif // GOOPERATOR_H
