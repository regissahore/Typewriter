#ifndef MCGOOPERATORFACTORY_H
#define MCGOOPERATORFACTORY_H
/**
 * 用于实例化对应的操作符，在类中定义了与操作符对应的类型号。
 * GO操作符本身不包含类型的信息，调用该类的创造函数可以自动设置操作符的类型。
 * 每次产生一个操作符，操作符会被赋给一个唯一的ID。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "MCGoAutoIncrementalFactory.h"
#include "MAGoOperator.h"

class MCGoOperatorFactory : public MCGoAutoIncrementalFactory
{
public:
    enum OperatorType {
        OPERATOR_TEST = 0,
        OPERATOR_1 = 1,
        OPERATOR_2 = 2,
        OPERATOR_3 = 3,
        OPERATOR_4 = 4,
        OPERATOR_5 = 5,
        OPERATOR_6 = 6,
        OPERATOR_7 = 7,
        OPERATOR_8 = 8,
        OPERATOR_9 = 9,
        OPERATOR_10 = 10,
        OPERATOR_11 = 11,
        OPERATOR_12 = 12,
        OPERATOR_13 = 13,
        OPERATOR_14 = 14,
        OPERATOR_15 = 15,
        OPERATOR_16 = 16,
        OPERATOR_17 = 17
    }; /** 对操作符类型的定义。 */
    MAGoOperator* getOperator(OperatorType type);
};

#endif // MCGOOPERATORFACTORY_H
