#ifndef PARAMETERGOOPERATOR_H
#define PARAMETERGOOPERATOR_H
/**
 * The parameter editor for GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOOperator : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOOperator(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    void addOperatorParameter();
    void addProbability0Parameter();
    void addProbability12Parameter();
    void addProbabilityMultipleParameter();
    void addOutputParameter();
    void addOperator9XYParameter();
    void addOperator11KParameter();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
    void itemClicked(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOOPERATOR_H
