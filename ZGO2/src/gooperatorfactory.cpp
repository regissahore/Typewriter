#include "gooperatorfactory.h"
#include "gooperator.h"
#include "goinput.h"
#include "gooutput.h"
#include "gostatus.h"

/**
 * Produce a GOOperator with auto increment ID.
 * @return Pointer to GOOperator.
 */
GOOperator* GOOperatorFactory::produce(const int type)
{
    GOOperator *op = new GOOperator();
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
    }
    return op;
}

bool GOOperatorFactory::isLogical(const int type)
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
