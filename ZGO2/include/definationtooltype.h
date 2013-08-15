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

        TOOL_TYPE_GO_POINTER_EXTEND,

        TOOL_TYPE_GO_TEXT,
        TOOL_TYPE_GO_OPERATOR_1,
        TOOL_TYPE_GO_OPERATOR_2,
        TOOL_TYPE_GO_OPERATOR_3,
        TOOL_TYPE_GO_OPERATOR_4,
        TOOL_TYPE_GO_OPERATOR_5,
        TOOL_TYPE_GO_OPERATOR_6,
        TOOL_TYPE_GO_OPERATOR_7,
        TOOL_TYPE_GO_OPERATOR_8,
        TOOL_TYPE_GO_OPERATOR_9,
        TOOL_TYPE_GO_OPERATOR_10,
        TOOL_TYPE_GO_OPERATOR_11,
        TOOL_TYPE_GO_OPERATOR_12,
        TOOL_TYPE_GO_OPERATOR_13,
        TOOL_TYPE_GO_OPERATOR_14,
        TOOL_TYPE_GO_OPERATOR_15,
        TOOL_TYPE_GO_OPERATOR_16,
        TOOL_TYPE_GO_OPERATOR_17,
        TOOL_TYPE_GO_SIGNAL,

        TOOL_TYPE_GO_MARKOV_TEXT,
        TOOL_TYPE_GO_MARKOV_POINTER_EXTEND,
        TOOL_TYPE_GO_MARKOV_OPERATOR_1,
        TOOL_TYPE_GO_MARKOV_OPERATOR_2,
        TOOL_TYPE_GO_MARKOV_OPERATOR_3,
        TOOL_TYPE_GO_MARKOV_OPERATOR_4,
        TOOL_TYPE_GO_MARKOV_OPERATOR_5,
        TOOL_TYPE_GO_MARKOV_OPERATOR_6,
        TOOL_TYPE_GO_MARKOV_OPERATOR_7,
        TOOL_TYPE_GO_MARKOV_OPERATOR_8,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9A1,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9A2,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9B,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9B1,
        TOOL_TYPE_GO_MARKOV_OPERATOR_9B2,
        TOOL_TYPE_GO_MARKOV_OPERATOR_10,
        TOOL_TYPE_GO_MARKOV_OPERATOR_11,
        TOOL_TYPE_GO_MARKOV_OPERATOR_11A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_12,
        TOOL_TYPE_GO_MARKOV_OPERATOR_12A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_13,
        TOOL_TYPE_GO_MARKOV_OPERATOR_13A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_13B,
        TOOL_TYPE_GO_MARKOV_OPERATOR_14,
        TOOL_TYPE_GO_MARKOV_OPERATOR_15,
        TOOL_TYPE_GO_MARKOV_OPERATOR_15A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_15B,
        TOOL_TYPE_GO_MARKOV_OPERATOR_16,
        TOOL_TYPE_GO_MARKOV_OPERATOR_17,
        TOOL_TYPE_GO_MARKOV_OPERATOR_18,
        TOOL_TYPE_GO_MARKOV_OPERATOR_18A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_19,
        TOOL_TYPE_GO_MARKOV_OPERATOR_20,
        TOOL_TYPE_GO_MARKOV_OPERATOR_21,
        TOOL_TYPE_GO_MARKOV_OPERATOR_22,
        TOOL_TYPE_GO_MARKOV_OPERATOR_22A,
        TOOL_TYPE_GO_MARKOV_OPERATOR_22B,
        TOOL_TYPE_GO_MARKOV_OPERATOR_23,
        TOOL_TYPE_GO_MARKOV_OPERATOR_24,
        TOOL_TYPE_GO_MARKOV_OPERATOR_25,
        TOOL_TYPE_GO_MARKOV_OPERATOR_26,
        TOOL_TYPE_GO_MARKOV_OPERATOR_27,
        TOOL_TYPE_GO_MARKOV_OPERATOR_28,
        TOOL_TYPE_GO_MARKOV_OPERATOR_29,
        TOOL_TYPE_GO_MARKOV_OPERATOR_SPLIT,
        TOOL_TYPE_GO_MARKOV_EQUIVALENT,
        TOOL_TYPE_GO_MARKOV_COMMON_CAUSE,
        TOOL_TYPE_GO_MARKOV_COMMON_CAUSE_2
    };
};

#endif // DEFINATIONTOOLTYPE_H
