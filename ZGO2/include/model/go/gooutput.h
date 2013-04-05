#ifndef GOOUTPUT_H
#define GOOUTPUT_H
/**
 * The output model of go operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOSignal;

class GOOutput
{
public:
    GOOutput();
    virtual ~GOOutput();
    int number() const;
    void setNumber(int num);
    QVector<QVector<GOSignal*>*>* signal() const;
    int getSignalIndex(GOSignal* signal) const;
    void addSignal(int index, GOSignal *signal);

private:
    QVector<QVector<GOSignal*>*> *_signal;
    void clear();
};

#endif // GOOUTPUT_H
