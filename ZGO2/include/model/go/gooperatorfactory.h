#ifndef GOOPERATORFACTORY_H
#define GOOPERATORFACTORY_H
/**
 * A GO Operator model factory.
 * The model produced will bind to a auto increment ID.
 * The start ID value must be set before use it beacause it is a static class.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "gooperator.h"

class GOOperatorFactory
{
public:
    enum OperatorType
    {
        Operator_Type_1 = 1,
        Operator_Type_2 = 2,
        Operator_Type_3 = 3,
        Operator_Type_4 = 4,
        Operator_Type_5 = 5,
        Operator_Type_6 = 6,
        Operator_Type_7 = 7,
        Operator_Type_8 = 8,
        Operator_Type_9 = 9,
        Operator_Type_10 = 10,
        Operator_Type_11 = 11,
        Operator_Type_12 = 12,
        Operator_Type_13 = 13,
        Operator_Type_14 = 14,
        Operator_Type_15 = 15,
        Operator_Type_16 = 16,
        Operator_Type_17 = 17
    };
    static GOOperator* produce(const int type);
    static void setID(const int id);
    static int currentID();

private:
    static int _autoID;
};

#endif // GOOPERATORFACTORY_H
