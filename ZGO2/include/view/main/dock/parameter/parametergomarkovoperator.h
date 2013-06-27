#ifndef PARAMETERGOMARKOVOPERATOR_H
#define PARAMETERGOMARKOVOPERATOR_H
/**
 * The parameter for GO operator in Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parametergooperator.h"

class ParameterGOMarkovOperator : public ParameterGOOperator
{
    Q_OBJECT
public:
    ParameterGOMarkovOperator(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    void addMarkovParameter();
    void addMarkovMulti1Parameter();
    void addMarkovMulti2Parameter();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOMARKOVOPERATOR_H
