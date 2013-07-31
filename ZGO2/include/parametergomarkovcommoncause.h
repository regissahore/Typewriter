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
    void setItemBreakdownTotal(double value);
    void setItemBreakdownIndividual(double value);
    void setItemGammaC(double value);
};

#endif // PARAMETERGOMARKOVCOMMONCAUSE_H
