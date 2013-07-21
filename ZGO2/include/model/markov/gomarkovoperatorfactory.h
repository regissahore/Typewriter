#ifndef GOMARKOVOPERATORFACTORY_H
#define GOMARKOVOPERATORFACTORY_H
/**
 * A operator model factory of Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QString>

class GOMarkovOperator;

class GOMarkovOperatorFactory
{
public:
    enum OperatorType
    {
        Operator_Type_1,
        Operator_Type_2,
        Operator_Type_3,
        Operator_Type_4,
        Operator_Type_5,
        Operator_Type_6,
        Operator_Type_7,
        Operator_Type_8,
        Operator_Type_9,
        Operator_Type_9A1,
        Operator_Type_9A2,
        Operator_Type_9B,
        Operator_Type_10,
        Operator_Type_11,
        Operator_Type_12,
        Operator_Type_12A,
        Operator_Type_13,
        Operator_Type_13A,
        Operator_Type_13B,
        Operator_Type_14,
        Operator_Type_15,
        Operator_Type_15A,
        Operator_Type_15B,
        Operator_Type_16,
        Operator_Type_17,
        Operator_Type_18,
        Operator_Type_18A,
        Operator_Type_19,
        Operator_Type_20,
        Operator_Type_21,
        Operator_Type_22,
        Operator_Type_22A,
        Operator_Type_22B,
        Operator_Type_23,
        Operator_Type_24,
        Operator_Type_25,
        Operator_Type_26,
        Operator_Type_27,
        Operator_Type_28,
        Operator_Type_29
    };
    static GOMarkovOperator* produce(const int type);
    static QString typeName(const int type);
    static bool isLogical(const int type);
};
#endif // GOMARKOVOPERATORFACTORY_H
