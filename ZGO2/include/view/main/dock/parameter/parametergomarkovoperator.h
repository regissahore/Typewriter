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
    void addTypeParameter();
    void addMarkovParameter();
    void addMarkov1Multi1Parameter();
    void addMarkov1Multi2Parameter();
    void addMarkov9FeedbackParameter();
    void addMarkov13Relation();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
    void itemClicked(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOMARKOVOPERATOR_H
