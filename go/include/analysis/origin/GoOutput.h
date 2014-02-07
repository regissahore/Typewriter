#ifndef GOOUTPUT_H
#define GOOUTPUT_H
#include <QVector>

class GoSignal;

class GoOutput
{
public:
    GoOutput();
    virtual ~GoOutput();
    int number() const;
    void setNumber(int num);
    QVector<QVector<GoSignal*>*>* signal() const;
    int getSignalIndex(GoSignal* signal) const;
    void addSignal(int index, GoSignal *signal);

private:
    QVector<QVector<GoSignal*>*> *_signal;
    void clear();
};

#endif // GOOUTPUT_H
