#include "messagetoolselection.h"

/**
 * 构造函数。
 */
MessageToolSelection::MessageToolSelection() : Message(), TypedItem()
{
    this->setName("Tool_Selection");
}

/**
 * 获取描述字符串。
 * @return 描述。
 */
QString MessageToolSelection::toString()
{
    QString str = "Type - ";
    switch (this->type())
    {
    case DefinationToolType::TOOL_TYPE_COMMON_NULL:
        str += "No Tool. ";
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_POINTER:
        str += "Pointer. ";
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_MOVE:
        str += "Move. ";
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_SELECT:
        str += "Select. ";
        break;
    case DefinationToolType::TOOL_TYPE_COMMON_ZOOM:
        str += "Zoom. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_TEXT:
        str += "Text. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
        str += "GO Operator 1. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
        str += "GO Operator 2. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
        str += "GO Operator 3. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
        str += "GO Operator 4. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
        str += "GO Operator 5. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
        str += "GO Operator 6. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
        str += "GO Operator 7. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
        str += "GO Operator 8. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
        str += "GO Operator 9. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
        str += "GO Operator 10. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
        str += "GO Operator 11. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
        str += "GO Operator 12. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
        str += "GO Operator 13. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
        str += "GO Operator 14. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
        str += "GO Operator 15. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
        str += "GO Operator 16. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        str += "GO Operator 17. ";
        break;
    case DefinationToolType::TOOL_TYPE_GO_SINGAL:
        str += "GO Signal. ";
        break;
    default:
        str += "Undefined Tool. ";
        break;
    }
    return str;
}
