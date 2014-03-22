#ifndef GOINPUT_H
#define GOINPUT_H
#include "stable.h"

class GoSignal;

class GoInput
{
public:
    GoInput();
    virtual ~GoInput();
    int number() const;
    void setNumber(int num);
    void add(GoSignal* signal);
    void set(int index, GoSignal* signal);
    void remove(int index);
    void clear();
    QVector<GoSignal*>* signal() const;
    int getSignalIndex(GoSignal* signal) const;

private:
    QVector<GoSignal*> *_signal;
};

#endif // GOINPUT_H
