#include "MCGoOperatorFactory.h"
#include "MCGoOperator1.h"
#include "MCGoOperator2.h"
#include "MCGoOperator3.h"
#include "MCGoOperator4.h"
#include "MCGoOperator5.h"
#include "MCGoOperator6.h"
#include "MCGoOperator7.h"
#include "MCGoOperator8.h"
#include "MCGoOperator9.h"
#include "MCGoOperator10.h"
#include "MCGoOperator11.h"
#include "MCGoOperator12.h"
#include "MCGoOperator13.h"
#include "MCGoOperator14.h"
#include "MCGoOperator15.h"
#include "MCGoOperator16.h"
#include "MCGoOperator17.h"
#include "MCGoOperatorTest.h"

MAGoOperator* MCGoOperatorFactory::getOperator(OperatorType type)
{
    switch(type)
    {
    case OPERATOR_1:
        return new MCGoOperator1();
    case OPERATOR_2:
        return new MCGoOperator2();
    case OPERATOR_3:
        return new MCGoOperator3();
    case OPERATOR_4:
        return new MCGoOperator4();
    case OPERATOR_5:
        return new MCGoOperator5();
    case OPERATOR_6:
        return new MCGoOperator6();
    case OPERATOR_7:
        return new MCGoOperator7();
    case OPERATOR_8:
        return new MCGoOperator8();
    case OPERATOR_9:
        return new MCGoOperator9();
    case OPERATOR_10:
        return new MCGoOperator10();
    case OPERATOR_11:
        return new MCGoOperator11();
    case OPERATOR_12:
        return new MCGoOperator12();
    case OPERATOR_13:
        return new MCGoOperator13();
    case OPERATOR_14:
        return new MCGoOperator14();
    case OPERATOR_15:
        return new MCGoOperator15();
    case OPERATOR_16:
        return new MCGoOperator16();
    case OPERATOR_17:
        return new MCGoOperator17();
    default:
        return new MCGoOperatorTest();
    }
}
