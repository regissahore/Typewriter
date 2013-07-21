#ifndef GOMARKOVOPERATOR2_H
#define GOMARKOVOPERATOR2_H
/**
 * 或门。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gomarkovoperator.h"

class GOMarkovOperator2 : public GOMarkovOperator
{
public:
    GOMarkovOperator2();
    ~GOMarkovOperator2();
    void calcOutputMarkovStatus(double time);
};

#endif // GOMARKOVOPERATOR1_H
