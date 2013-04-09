#ifndef GOMARKOVEQUIVALENT_H
#define GOMARKOVEQUIVALENT_H
/**
 * The equivalent in the GO Markov Repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>

class GOMarkovStatus;
class GOMarkovOperator;

class GOMarkovEquivalent
{
public:
    GOMarkovEquivalent();
    virtual ~GOMarkovEquivalent();
    QVector<GOMarkovOperator *> *operators() const;
    QVector<GOMarkovEquivalent *> *equivalents() const;
    int I() const;
    int L() const;
    int J() const;
    void setI(const int value);
    void setL(const int value);
    void setJ(const int value);
    virtual GOMarkovStatus getEquivalentStatus() = 0;

protected:
    QVector<GOMarkovOperator*> *_operators;
    QVector<GOMarkovEquivalent*> *_equivalents;
    int _I; /** Shutdown. */
    int _L; /** Repair. */
    int _J; /** Backup. */
};

#endif // GOMARKOVEQUIVALENT_H
