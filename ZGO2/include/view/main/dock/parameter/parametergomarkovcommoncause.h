#ifndef PARAMETERGOMARKOVCOMMONCAUSE_H
#define PARAMETERGOMARKOVCOMMONCAUSE_H
/**
 * The parameter for the common cause in GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOMarkovCommonCause : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovCommonCause(QWidget *parent = 0);
    void bindItem(void *item);

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOMARKOVCOMMONCAUSE_H
