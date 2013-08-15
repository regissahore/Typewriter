#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gomarkovoperator1.h"
#include "gomarkovoperator2.h"
#include "gomarkovoperator3.h"
#include "gomarkovoperator4.h"
#include "gomarkovoperator5.h"
#include "gomarkovoperator6.h"
#include "gomarkovoperator7.h"
#include "gomarkovoperator8.h"
#include "gomarkovoperator9.h"
#include "gomarkovoperator9a.h"
#include "gomarkovoperator9a1.h"
#include "gomarkovoperator9a2.h"
#include "gomarkovoperator9b.h"
#include "gomarkovoperator9b1.h"
#include "gomarkovoperator9b2.h"
#include "gomarkovoperator10.h"
#include "gomarkovoperator11.h"
#include "gomarkovoperator11a.h"
#include "gomarkovoperator12.h"
#include "gomarkovoperator12a.h"
#include "gomarkovoperator13.h"
#include "gomarkovoperator13a.h"
#include "gomarkovoperator13b.h"
#include "gomarkovoperator14.h"
#include "gomarkovoperator15.h"
#include "gomarkovoperator15a.h"
#include "gomarkovoperator15b.h"
#include "gomarkovoperator16.h"
#include "gomarkovoperator17.h"
#include "gomarkovoperator18.h"
#include "gomarkovoperator18a.h"
#include "gomarkovoperator19.h"
#include "gomarkovoperator20.h"
#include "gomarkovoperator21.h"
#include "gomarkovoperator22.h"
#include "gomarkovoperator22a.h"
#include "gomarkovoperator22b.h"
#include "gomarkovoperator23.h"
#include "gomarkovoperator24.h"
#include "gomarkovoperator25.h"
#include "gomarkovoperator26.h"
#include "gomarkovoperator27.h"
#include "gomarkovoperator28.h"
#include "gomarkovoperator29.h"
#include "gomarkovoperatorsplitpoint.h"

/**
 * Produce a GOOperator with auto increment ID.
 * @return Pointer to GOOperator.
 */
GOMarkovOperator* GOMarkovOperatorFactory::produce(const int type)
{
    GOMarkovOperator *op;
    switch (type)
    {
    case Operator_Type_1:
        op = new GOMarkovOperator1();
        break;
    case Operator_Type_2:
        op = new GOMarkovOperator2();
        break;
    case Operator_Type_3:
        op = new GOMarkovOperator3();
        break;
    case Operator_Type_4:
        op = new GOMarkovOperator4();
        break;
    case Operator_Type_5:
        op = new GOMarkovOperator5();
        break;
    case Operator_Type_6:
        op = new GOMarkovOperator6();
        break;
    case Operator_Type_7:
        op = new GOMarkovOperator7();
        break;
    case Operator_Type_8:
        op = new GOMarkovOperator8();
        break;
    case Operator_Type_9:
        op = new GOMarkovOperator9();
        break;
    case Operator_Type_9A:
        op = new GOMarkovOperator9A();
        break;
    case Operator_Type_9A1:
        op = new GOMarkovOperator9A1();
        break;
    case Operator_Type_9A2:
        op = new GOMarkovOperator9A2();
        break;
    case Operator_Type_9B:
        op = new GOMarkovOperator9B();
        break;
    case Operator_Type_9B1:
        op = new GOMarkovOperator9B1();
        break;
    case Operator_Type_9B2:
        op = new GOMarkovOperator9B2();
        break;
    case Operator_Type_10:
        op = new GOMarkovOperator10();
        break;
    case Operator_Type_11:
        op = new GOMarkovOperator11();
        break;
    case Operator_Type_11A:
        op = new GOMarkovOperator11A();
        break;
    case Operator_Type_12:
        op = new GOMarkovOperator12();
        break;
    case Operator_Type_12A:
        op = new GOMarkovOperator12A();
        break;
    case Operator_Type_13:
        op = new GOMarkovOperator13();
        break;
    case Operator_Type_13A:
        op = new GOMarkovOperator13A();
        break;
    case Operator_Type_13B:
        op = new GOMarkovOperator13B();
        break;
    case Operator_Type_14:
        op = new GOMarkovOperator14();
        break;
    case Operator_Type_15:
        op = new GOMarkovOperator15();
        break;
    case Operator_Type_15A:
        op = new GOMarkovOperator15A();
        break;
    case Operator_Type_15B:
        op = new GOMarkovOperator15B();
        break;
    case Operator_Type_16:
        op = new GOMarkovOperator16();
        break;
    case Operator_Type_17:
        op = new GOMarkovOperator17();
        break;
    case Operator_Type_18:
        op = new GOMarkovOperator18();
        break;
    case Operator_Type_18A:
        op = new GOMarkovOperator18A();
        break;
    case Operator_Type_19:
        op = new GOMarkovOperator19();
        break;
    case Operator_Type_20:
        op = new GOMarkovOperator20();
        break;
    case Operator_Type_21:
        op = new GOMarkovOperator21();
        break;
    case Operator_Type_22:
        op = new GOMarkovOperator22();
        break;
    case Operator_Type_22A:
        op = new GOMarkovOperator22A();
        break;
    case Operator_Type_22B:
        op = new GOMarkovOperator22B();
        break;
    case Operator_Type_23:
        op = new GOMarkovOperator23();
        break;
    case Operator_Type_24:
        op = new GOMarkovOperator24();
        break;
    case Operator_Type_25:
        op = new GOMarkovOperator25();
        break;
    case Operator_Type_26:
        op = new GOMarkovOperator26();
        break;
    case Operator_Type_27:
        op = new GOMarkovOperator27();
        break;
    case Operator_Type_28:
        op = new GOMarkovOperator28();
        break;
    case Operator_Type_29:
        op = new GOMarkovOperator29();
        break;
    case Operator_Type_Split:
        op = new GOMarkovOperatorSplitPoint();
        break;
    }
    op->setType(type);
    return op;
}

QString GOMarkovOperatorFactory::typeName(const int type)
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

bool GOMarkovOperatorFactory::isLogical(const int type)
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

bool GOMarkovOperatorFactory::isCommonPossible(const int type)
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
