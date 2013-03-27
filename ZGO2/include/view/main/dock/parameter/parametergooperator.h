#ifndef PARAMETERGOOPERATOR_H
#define PARAMETERGOOPERATOR_H
/**
 * The parameter editor for GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOOperator : public ParameterAbstract
{
public:
    ParameterGOOperator(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    void addOperatorParameter();
    void addStatusParameter();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOOPERATOR_H
