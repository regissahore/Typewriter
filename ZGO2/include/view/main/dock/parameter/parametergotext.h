#ifndef PARAMETERGOTEXT_H
#define PARAMETERGOTEXT_H
/**
 * The parameter editor for GO text.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOText : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOText(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    void addTextParameter();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOTEXT_H
