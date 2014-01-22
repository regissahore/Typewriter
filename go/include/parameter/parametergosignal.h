#ifndef PARAMETERGOSIGNAL_H
#define PARAMETERGOSIGNAL_H
#include "ParameterAbstract.h"

class ParameterGoSignal : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGoSignal(QWidget *parent = 0);
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
