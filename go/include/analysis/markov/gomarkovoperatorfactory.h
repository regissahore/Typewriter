#ifndef GOMARKOVOPERATORFACTORY_H
#define GOMARKOVOPERATORFACTORY_H
#include <QString>

class GoMarkovOperator;

class GoMarkovOperatorFactory
{
public:
    enum OperatorType
    {
        Operator_Type_1 = 0,
        Operator_Type_2 = 1,
        Operator_Type_3 = 2,
        Operator_Type_4 = 3,
        Operator_Type_5 = 4,
        Operator_Type_6 = 5,
        Operator_Type_7 = 6,
        Operator_Type_8 = 7,
        Operator_Type_9 = 8,
        Operator_Type_9A = 9,
        Operator_Type_9A1 = 10,
        Operator_Type_9A2 = 11,
        Operator_Type_9B = 12,
        Operator_Type_9B1 = 13,
        Operator_Type_9B2 = 14,
        Operator_Type_10 = 15,
        Operator_Type_11 = 16,
        Operator_Type_11A = 43,
        Operator_Type_12 = 17,
        Operator_Type_12A = 18,
        Operator_Type_13 = 19,
        Operator_Type_13A = 20,
        Operator_Type_13B = 21,
        Operator_Type_14 = 22,
        Operator_Type_15 = 23,
        Operator_Type_15A = 24,
        Operator_Type_15B = 25,
        Operator_Type_16 = 26,
        Operator_Type_17 = 27,
        Operator_Type_18 = 28,
        Operator_Type_18A = 29,
        Operator_Type_19 = 30,
        Operator_Type_20 = 31,
        Operator_Type_21 = 32,
        Operator_Type_22 = 33,
        Operator_Type_22A = 34,
        Operator_Type_22B = 35,
        Operator_Type_23 = 36,
        Operator_Type_24 = 37,
        Operator_Type_25 = 38,
        Operator_Type_26 = 39,
        Operator_Type_27 = 40,
        Operator_Type_28 = 41,
        Operator_Type_29 = 42,
        Operator_Type_Split = 44,
        Operator_Total = 45
    };
    static GoMarkovOperator* produce(const int type);
    static QString typeName(const int type);
    static bool isLogical(const int type);
    static bool isCommonPossible(const int type);
    static bool isVectorInput(const int type);
    static bool isVectorSubInput(const int type);
    static bool isVectorOutput(const int type);
};
#endif // GOMARKOVOPERATORFACTORY_H
