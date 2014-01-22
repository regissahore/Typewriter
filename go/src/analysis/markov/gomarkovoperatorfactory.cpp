#include "GoMarkovOperatorFactory.h"
#include "GoMarkovOperator.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoStatus.h"
#include "GoMarkovOperator1.h"
#include "GoMarkovOperator2.h"
#include "GoMarkovOperator3.h"
#include "GoMarkovOperator4.h"
#include "GoMarkovOperator5.h"
#include "GoMarkovOperator6.h"
#include "GoMarkovOperator7.h"
#include "GoMarkovOperator8.h"
#include "GoMarkovOperator9.h"
#include "GoMarkovOperator9a.h"
#include "GoMarkovOperator9a1.h"
#include "GoMarkovOperator9a2.h"
#include "GoMarkovOperator9b.h"
#include "GoMarkovOperator9b1.h"
#include "GoMarkovOperator9b2.h"
#include "GoMarkovOperator10.h"
#include "GoMarkovOperator11.h"
#include "GoMarkovOperator11a.h"
#include "GoMarkovOperator12.h"
#include "GoMarkovOperator12a.h"
#include "GoMarkovOperator13.h"
#include "GoMarkovOperator13a.h"
#include "GoMarkovOperator13b.h"
#include "GoMarkovOperator14.h"
#include "GoMarkovOperator15.h"
#include "GoMarkovOperator15a.h"
#include "GoMarkovOperator15b.h"
#include "GoMarkovOperator16.h"
#include "GoMarkovOperator17.h"
#include "GoMarkovOperator18.h"
#include "GoMarkovOperator18a.h"
#include "GoMarkovOperator19.h"
#include "GoMarkovOperator20.h"
#include "GoMarkovOperator21.h"
#include "GoMarkovOperator22.h"
#include "GoMarkovOperator22a.h"
#include "GoMarkovOperator22b.h"
#include "GoMarkovOperator23.h"
#include "GoMarkovOperator24.h"
#include "GoMarkovOperator25.h"
#include "GoMarkovOperator26.h"
#include "GoMarkovOperator27.h"
#include "GoMarkovOperator28.h"
#include "GoMarkovOperator29.h"
#include "GoMarkovOperatorSplitPoint.h"

GoMarkovOperator* GoMarkovOperatorFactory::produce(const int type)
{
    GoMarkovOperator *op;
    switch (type)
    {
    case Operator_Type_1:
        op = new GoMarkovOperator1();
        break;
    case Operator_Type_2:
        op = new GoMarkovOperator2();
        break;
    case Operator_Type_3:
        op = new GoMarkovOperator3();
        break;
    case Operator_Type_4:
        op = new GoMarkovOperator4();
        break;
    case Operator_Type_5:
        op = new GoMarkovOperator5();
        break;
    case Operator_Type_6:
        op = new GoMarkovOperator6();
        break;
    case Operator_Type_7:
        op = new GoMarkovOperator7();
        break;
    case Operator_Type_8:
        op = new GoMarkovOperator8();
        break;
    case Operator_Type_9:
        op = new GoMarkovOperator9();
        break;
    case Operator_Type_9A:
        op = new GoMarkovOperator9A();
        break;
    case Operator_Type_9A1:
        op = new GoMarkovOperator9A1();
        break;
    case Operator_Type_9A2:
        op = new GoMarkovOperator9A2();
        break;
    case Operator_Type_9B:
        op = new GoMarkovOperator9B();
        break;
    case Operator_Type_9B1:
        op = new GoMarkovOperator9B1();
        break;
    case Operator_Type_9B2:
        op = new GoMarkovOperator9B2();
        break;
    case Operator_Type_10:
        op = new GoMarkovOperator10();
        break;
    case Operator_Type_11:
        op = new GoMarkovOperator11();
        break;
    case Operator_Type_11A:
        op = new GoMarkovOperator11A();
        break;
    case Operator_Type_12:
        op = new GoMarkovOperator12();
        break;
    case Operator_Type_12A:
        op = new GoMarkovOperator12A();
        break;
    case Operator_Type_13:
        op = new GoMarkovOperator13();
        break;
    case Operator_Type_13A:
        op = new GoMarkovOperator13A();
        break;
    case Operator_Type_13B:
        op = new GoMarkovOperator13B();
        break;
    case Operator_Type_14:
        op = new GoMarkovOperator14();
        break;
    case Operator_Type_15:
        op = new GoMarkovOperator15();
        break;
    case Operator_Type_15A:
        op = new GoMarkovOperator15A();
        break;
    case Operator_Type_15B:
        op = new GoMarkovOperator15B();
        break;
    case Operator_Type_16:
        op = new GoMarkovOperator16();
        break;
    case Operator_Type_17:
        op = new GoMarkovOperator17();
        break;
    case Operator_Type_18:
        op = new GoMarkovOperator18();
        break;
    case Operator_Type_18A:
        op = new GoMarkovOperator18A();
        break;
    case Operator_Type_19:
        op = new GoMarkovOperator19();
        break;
    case Operator_Type_20:
        op = new GoMarkovOperator20();
        break;
    case Operator_Type_21:
        op = new GoMarkovOperator21();
        break;
    case Operator_Type_22:
        op = new GoMarkovOperator22();
        break;
    case Operator_Type_22A:
        op = new GoMarkovOperator22A();
        break;
    case Operator_Type_22B:
        op = new GoMarkovOperator22B();
        break;
    case Operator_Type_23:
        op = new GoMarkovOperator23();
        break;
    case Operator_Type_24:
        op = new GoMarkovOperator24();
        break;
    case Operator_Type_25:
        op = new GoMarkovOperator25();
        break;
    case Operator_Type_26:
        op = new GoMarkovOperator26();
        break;
    case Operator_Type_27:
        op = new GoMarkovOperator27();
        break;
    case Operator_Type_28:
        op = new GoMarkovOperator28();
        break;
    case Operator_Type_29:
        op = new GoMarkovOperator29();
        break;
    case Operator_Type_Split:
        op = new GoMarkovOperatorSplitPoint();
        break;
    }
    op->setType(type);
    return op;
}

QString GoMarkovOperatorFactory::typeName(const int type)
{
    switch (type)
    {
    case Operator_Type_1:
        return "1";
    case Operator_Type_2:
        return "2";
    case Operator_Type_3:
        return "3";
    case Operator_Type_4:
        return "4";
    case Operator_Type_5:
        return "5";
    case Operator_Type_6:
        return "6";
    case Operator_Type_7:
        return "7";
    case Operator_Type_8:
        return "8";
    case Operator_Type_9:
        return "9";
    case Operator_Type_9A:
        return "9A";
    case Operator_Type_9A1:
        return "9A1";
    case Operator_Type_9A2:
        return "9A2";
    case Operator_Type_9B:
        return "9B";
    case Operator_Type_9B1:
        return "9B1";
    case Operator_Type_9B2:
        return "9B2";
    case Operator_Type_10:
        return "10";
    case Operator_Type_11:
        return "11";
    case Operator_Type_11A:
        return "11A";
    case Operator_Type_12:
        return "12";
    case Operator_Type_12A:
        return "12A";
    case Operator_Type_13:
        return "13";
    case Operator_Type_13A:
        return "13A";
    case Operator_Type_13B:
        return "13B";
    case Operator_Type_14:
        return "14";
    case Operator_Type_15:
        return "15";
    case Operator_Type_15A:
        return "15A";
    case Operator_Type_15B:
        return "15B";
    case Operator_Type_16:
        return "16";
    case Operator_Type_17:
        return "17";
    case Operator_Type_18:
        return "18";
    case Operator_Type_18A:
        return "18A";
    case Operator_Type_19:
        return "19";
    case Operator_Type_20:
        return "20";
    case Operator_Type_21:
        return "21";
    case Operator_Type_22:
        return "22";
    case Operator_Type_22A:
        return "22A";
    case Operator_Type_22B:
        return "22B";
    case Operator_Type_23:
        return "23";
    case Operator_Type_24:
        return "24";
    case Operator_Type_25:
        return "25";
    case Operator_Type_26:
        return "26";
    case Operator_Type_27:
        return "27";
    case Operator_Type_28:
        return "28";
    case Operator_Type_29:
        return "29";
    case Operator_Type_Split:
        return "Split";
    }
    return "No Name";
}

bool GoMarkovOperatorFactory::isLogical(const int type)
{
    switch (type)
    {
    case Operator_Type_2:
    case Operator_Type_10:
    case Operator_Type_11:
    case Operator_Type_11A:
    case Operator_Type_12A:
    case Operator_Type_15B:
    case Operator_Type_20:
    case Operator_Type_23:
    case Operator_Type_Split:
        return true;
    }
    return false;
}

bool GoMarkovOperatorFactory::isCommonPossible(const int type)
{
    switch (type)
    {
    case Operator_Type_2:
    case Operator_Type_6:
    case Operator_Type_7:
    case Operator_Type_9B1:
    case Operator_Type_9B2:
    case Operator_Type_10:
    case Operator_Type_11:
    case Operator_Type_13A:
    case Operator_Type_13B:
    case Operator_Type_16:
    case Operator_Type_17:
    case Operator_Type_20:
    case Operator_Type_22A:
    case Operator_Type_22B:
    case Operator_Type_23:
        return true;
    }
    return false;
}
