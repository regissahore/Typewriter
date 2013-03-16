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
        EDITOR_SELECTION_NULL,          /** 没有选择编辑器。 */
        EDITOR_SELECTION_GO_OPERATOR,   /** 选择GO操作符。 */
        EDITOR_SELECTION_GO_SIGNAL      /** 选择GO信号流。 */
    };
};

#endif // DEFINATIONEDITORSELECTIONTYPE_H
