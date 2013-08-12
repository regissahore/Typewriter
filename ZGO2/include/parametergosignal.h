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
    void addIDParameter();
    void addSignalParameter();

protected slots:
    void setItemID(int value);
    void setIsStraightLine(bool value);
    void setIsGlobalFeedback(bool value);
};

#endif // PARAMETERGOSIGNAL_H
