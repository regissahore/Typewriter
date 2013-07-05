#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"
#include "gomarkovoperator1e1.h"
#include "gomarkovoperator9a1.h"
#include "gomarkovoperator9a2.h"
#include "gomarkovoperator13a.h"
#include "gomarkovoperator13b.h"
#include "gomarkovoperator15a.h"

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
    case Operator_Type_2:
    case Operator_Type_3:
    case Operator_Type_4:
    case Operator_Type_5:
    case Operator_Type_6:
    case Operator_Type_7:
    case Operator_Type_8:
    case Operator_Type_9:
    case Operator_Type_10:
    case Operator_Type_11:
    case Operator_Type_12:
    case Operator_Type_13:
    case Operator_Type_14:
    case Operator_Type_15:
    case Operator_Type_16:
    case Operator_Type_17:
        op = new GOMarkovOperator();
        break;
    case Operator_Type_1_E1:
        op = new GOMarkovOperator1E1();
        break;
    case Operator_Type_9_A1:
        op = new GOMarkovOperator9A1();
        break;
    case Operator_Type_9_A2:
        op = new GOMarkovOperator9A2();
        break;
    case Operator_Type_13_A:
        op = new GOMarkovOperator13A();
        break;
    case Operator_Type_13_B:
        op = new GOMarkovOperator13B();
        break;
    case Operator_Type_15_A:
        op = new GOMarkovOperator15A();
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
    case Operator_Type_1_E1:
        op->input()->setNumber(1);
        op->subInput()->setNumber(0);
        op->output()->setNumber(1);
        break;
    }
    return op;
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

