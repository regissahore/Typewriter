#ifndef GOINPUT_H
#define GOINPUT_H
#include <QVector>

class GOSignal;

class GOInput
{
public:
    GOInput();
    virtual ~GOInput();
    int number() const;
    void setNumber(int num);
    void add(GOSignal* signal);
    void set(int index, GOSignal* signal);
    void remove(int index);
    QVector<GOSignal*>* signal() const;
    int getSignalIndex(GOSignal* signal) const;

private:
    QVector<GOSignal*> *_signal;
};

#endif // GOINPUT_H
