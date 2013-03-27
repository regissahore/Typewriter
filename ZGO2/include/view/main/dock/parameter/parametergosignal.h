#ifndef PARAMETERGOSIGNAL_H
#define PARAMETERGOSIGNAL_H
/**
 * The parameter editor for GO signal.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class ParameterGOSignal : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOSignal(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    void addSignalParameter();

protected slots:
    void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERGOSIGNAL_H
