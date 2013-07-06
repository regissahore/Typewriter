#ifndef DIALOG13AINPUT_H
#define DIALOG13AINPUT_H
/**
 * The input dialog of GO Markov operator 13.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "dialogmatrixinput.h"

class GOMarkovOperator13;

class Dialog13AInput : public DialogMatrixInput
{
    Q_OBJECT

public:
    explicit Dialog13AInput(QWidget *parent = 0);
    void setOperator(GOMarkovOperator13* op);
    void saveChange();

private:
    GOMarkovOperator13* _op;
};

#endif // DIALOG13AINPUT_H
