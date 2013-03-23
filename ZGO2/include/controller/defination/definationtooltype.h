#ifndef DEFINATIONTOOLTYPE_H
#define DEFINATIONTOOLTYPE_H
/**
 * 工具类型的定义。
 * @author ZHG <CyberZHG@gmail.com>
 */
class DefinationToolType
{
public:
    enum ToolType
    {
        TOOL_TYPE_COMMON_NULL,          /** 没有工具。 */
        TOOL_TYPE_COMMON_POINTER,       /** 单选工具。 */
        TOOL_TYPE_COMMON_SELECT,        /** 多选工具。 */
        TOOL_TYPE_COMMON_MOVE,          /** 移动工具。 */
        TOOL_TYPE_COMMON_ZOOM,          /** 缩放工具。 */

        TOOL_TYPE_GO_TEXT,              /** 文本工具。 */
        TOOL_TYPE_GO_OPERATOR_1,        /** 第1类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_2,        /** 第2类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_3,        /** 第3类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_4,        /** 第4类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_5,        /** 第5类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_6,        /** 第6类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_7,        /** 第7类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_8,        /** 第8类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_9,        /** 第9类GO操作幅。 */
        TOOL_TYPE_GO_OPERATOR_10,       /** 第10类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_11,       /** 第11类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_12,       /** 第12类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_13,       /** 第13类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_14,       /** 第14类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_15,       /** 第15类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_16,       /** 第16类GO操作符。 */
        TOOL_TYPE_GO_OPERATOR_17,       /** 第17类GO操作符。 */
        TOOL_TYPE_GO_SIGNAL             /** GO信号流。 */
    };
};

#endif // DEFINATIONTOOLTYPE_H
