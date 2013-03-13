#include "VCGoUnitFactory.h"
#include "VCGoOperator1.h"
#include "VCGoOperator2.h"
#include "VCGoOperator3.h"
#include "VCGoOperator4.h"
#include "VCGoOperator5.h"
#include "VCGoOperator6.h"
#include "VCGoOperator7.h"
#include "VCGoOperator8.h"
#include "VCGoOperator9.h"
#include "VCGoOperator10.h"
#include "VCGoOperator11.h"
#include "VCGoOperator12.h"
#include "VCGoOperator13.h"
#include "VCGoOperator14.h"
#include "VCGoOperator15.h"
#include "VCGoOperator16.h"
#include "VCGoOperator17.h"
#include "VCGoOperatorTest.h"
#include "VCGoSeriesSet.h"

VAGoUnit* VCGoUnitFactory::getUnit(UnitType type)
{
    switch (type)
    {
    case OPERATOR_1:
        return new VCGoOperator1();
    case OPERATOR_2:
        return new VCGoOperator2();
    case OPERATOR_3:
        return new VCGoOperator3();
    case OPERATOR_4:
        return new VCGoOperator4();
    case OPERATOR_5:
        return new VCGoOperator5();
    case OPERATOR_6:
        return new VCGoOperator6();
    case OPERATOR_7:
        return new VCGoOperator7();
    case OPERATOR_8:
        return new VCGoOperator8();
    case OPERATOR_9:
        return new VCGoOperator9();
    case OPERATOR_10:
        return new VCGoOperator10();
    case OPERATOR_11:
        return new VCGoOperator14();
    case OPERATOR_12:
        return new VCGoOperator15();
    case OPERATOR_13:
        return new VCGoOperator13();
    case OPERATOR_14:
        return new VCGoOperator14();
    case OPERATOR_15:
        return new VCGoOperator15();
    case OPERATOR_16:
        return new VCGoOperator16();
    case OPERATOR_17:
        return new VCGoOperator17();
    case OPERATOR_SERIES_SET:
        return new VCGoSeriesSet();
    default:
        return new VCGoOperatorTest();
    }
}
