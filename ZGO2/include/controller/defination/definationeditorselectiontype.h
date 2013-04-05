#ifndef DEFINATIONEDITORSELECTIONTYPE_H
#define DEFINATIONEDITORSELECTIONTYPE_H
/**
 * 对编辑器选择内容的定义。
 * @author ZHG <CyberZHG@gmail.com>
 */

class DefinationEditorSelectionType
{
public:
    enum EditorSelectionType
    {
        EDITOR_SELECTION_NULL,          /** 编辑器没有选择。 */
        EDITOR_SELECTION_GO_OPERATOR,   /** 选择GO操作符。 */
        EDITOR_SELECTION_GO_SIGNAL,     /** 选择GO信号流。 */
        EDITOR_SELECTION_GO_TEXT,
        EDITOR_SELECTION_GO_MARKOV_OPERATOR,
        EDITOR_SELECTION_GO_MARKOV_SIGNAL
    };
};

#endif // DEFINATIONEDITORSELECTIONTYPE_H
