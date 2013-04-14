#ifndef PARAMETERGOMARKOVEQUIVALENT_H
#define PARAMETERGOMARKOVEQUIVALENT_H
/**
 * The parameter for the equivalent in GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOMarkovEquivalent : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovEquivalent(QWidget *parent = 0);
    void bindItem(void *item);

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOMARKOVEQUIVALENT_H
