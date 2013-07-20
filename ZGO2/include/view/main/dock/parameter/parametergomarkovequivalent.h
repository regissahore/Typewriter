#ifndef PARAMETERGOMARKOVEQUIVALENT_H
#define PARAMETERGOMARKOVEQUIVALENT_H
/**
 * The parameter for the equivalent in GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class QSpinBox;

class ParameterGOMarkovEquivalent : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOMarkovEquivalent(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QSpinBox *_spinBoxI;
    QSpinBox *_spinBoxL;
    QSpinBox *_spinBoxJ;

protected slots:
    void setItemI(int value);
    void setItemL(int value);
    void setItemJ(int value);
};

#endif // PARAMETERGOMARKOVEQUIVALENT_H
