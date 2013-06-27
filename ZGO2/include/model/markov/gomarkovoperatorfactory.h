#ifndef GOMARKOVOPERATORFACTORY_H
#define GOMARKOVOPERATORFACTORY_H
/**
 * A operator model factory of Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
class GOMarkovOperator;

class GOMarkovOperatorFactory
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
        Operator_Type_17 = 17,
        Operator_Type_1_E1 // Two breakdown status operator.
    };
    static GOMarkovOperator* produce(const int type);
    static bool isLogical(const int type);
};
#endif // GOMARKOVOPERATORFACTORY_H
