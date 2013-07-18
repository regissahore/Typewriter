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
#include "gomarkovoperator9a1.h"
#include "gomarkovoperator9a2.h"
#include "gomarkovoperator9b.h"
#include "gomarkovoperator10.h"
#include "gomarkovoperator11.h"
#include "gomarkovoperator12.h"
#include "gomarkovoperator13.h"
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
    case Operator_Type_9A1:
        op = new GOMarkovOperator9A1();
        break;
    case Operator_Type_9A2:
        op = new GOMarkovOperator9A2();
        break;
    case Operator_Type_9B:
        op = new GOMarkovOperator9B();
        break;
    case Operator_Type_10:
        op = new GOMarkovOperator10();
        break;
    case Operator_Type_11:
        op = new GOMarkovOperator11();
        break;
    case Operator_Type_12:
        op = new GOMarkovOperator12();
        break;
    case Operator_Type_13:
        op = new GOMarkovOperator13();
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
    }
    op->setType(type);
    return op;
    /*GOMarkovOperator *op;
    switch (type)
    {
    case Operator_Type_9_A1:
    case Operator_Type_9_A2:
        op = new GOMarkovOperator9A();
        break;
    case Operator_Type_13_A:
    case Operator_Type_13_B:
        op = new GOMarkovOperator13();
        break;
    default:
        op = new GOMarkovOperator();
        break;
    }
    op->setType(type);
    switch (type)
    {
    case Operator_Type_1:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_2:
        op->input()->setNumber(2);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        op->status()->setNumber(0);
        break;
    case Operator_Type_3:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_4:
        op->input()->setNumber(0);
        op->subInput()->setNumber(0);
        op->output()->setNumber(3);
        break;
    case Operator_Type_5:
        op->input()->setNumber(0);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_6:
        op->input()->setNumber(1);
        op->subInput()->setNumber(1);
        op->output()->setNumber(1);
        break;
    case Operator_Type_7:
        op->input()->setNumber(1);
        op->subInput()->setNumber(1);
        op->output()->setNumber(1);
        break;
    case Operator_Type_8:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_9:
        op->input()->setNumber(1);
        op->subInput()->setNumber(1);
        op->output()->setNumber(1);
        break;
    case Operator_Type_10:
        op->input()->setNumber(2);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        op->status()->setNumber(0);
        break;
    case Operator_Type_11:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        op->status()->setNumber(0);
        break;
    case Operator_Type_12:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(2);
        break;
    case Operator_Type_13:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(3);
        break;
    case Operator_Type_14:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_15:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_16:
        op->input()->setNumber(1);
        op->subInput()->setNumber(1);
        op->output()->setNumber(1);
        break;
    case Operator_Type_17:
        op->input()->setNumber(1);
        op->subInput()->setNumber(1);
        op->output()->setNumber(1);
        break;
    case Operator_Type_9_A1:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_9_A2:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    case Operator_Type_13_A:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(3);
        break;
    case Operator_Type_13_B:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(3);
        break;
    case Operator_Type_15_A:
        op->input()->setNumber(3);
        op->subInput()->setNumber(0);
        op->output()->setNumber(3);
        break;
    }
    return op;*/
}

bool GOMarkovOperatorFactory::isLogical(const int type)
{
    switch (type)
    {
    case Operator_Type_2:
        return true;
    case Operator_Type_10:
        return true;
    case Operator_Type_11:
        return true;
    }
    return false;
}

