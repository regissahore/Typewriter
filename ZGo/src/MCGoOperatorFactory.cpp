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

/**
 * 获得GO操作符的对象。
 * @param type 操作符的类型。
 * @param id 操作符的ID。
 * @return 实例化后的对象，如果类型不存在返回空指针。
 */
MAGoOperator* MCGoOperatorFactory::getOperator(OperatorType type)
{
    MAGoOperator* go = 0L;
    switch(type)
    {
    case OPERATOR_1:
        go = new MCGoOperator1();
        break;
    case OPERATOR_2:
        go = new MCGoOperator2();
        break;
    case OPERATOR_3:
        go = new MCGoOperator3();
        break;
    case OPERATOR_4:
        go = new MCGoOperator4();
        break;
    case OPERATOR_5:
        go = new MCGoOperator5();
        break;
    case OPERATOR_6:
        go = new MCGoOperator6();
        break;
    case OPERATOR_7:
        go = new MCGoOperator7();
        break;
    case OPERATOR_8:
        go = new MCGoOperator8();
        break;
    case OPERATOR_9:
        go = new MCGoOperator9();
        break;
    case OPERATOR_10:
        go = new MCGoOperator10();
        break;
    case OPERATOR_11:
        go = new MCGoOperator11();
        break;
    case OPERATOR_12:
        go = new MCGoOperator12();
        break;
    case OPERATOR_13:
        go = new MCGoOperator13();
        break;
    case OPERATOR_14:
        go = new MCGoOperator14();
        break;
    case OPERATOR_15:
        go = new MCGoOperator15();
        break;
    case OPERATOR_16:
        go = new MCGoOperator16();
        break;
    case OPERATOR_17:
        go = new MCGoOperator17();
        break;
    case OPERATOR_TEST:
        go = new MCGoOperatorTest();
        break;
    }
    if (go)
    {
        go->setId(this->id());
        go->setType(type);
    }
    return go;
}
