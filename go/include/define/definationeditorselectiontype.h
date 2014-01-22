#ifndef DEFINATIONEDITORSELECTIONTYPE_H
#define DEFINATIONEDITORSELECTIONTYPE_H

class DefinationEditorSelectionType
{
public:
    enum EditorSelectionType
    {
        EDITOR_SELECTION_NULL,          /** 编辑器没有选择。 */
        EDITOR_SELECTION_EMPTY,
        EDITOR_SELECTION_Go_OPERATOR,   /** 选择Go操作符。 */
        EDITOR_SELECTION_Go_SIGNAL,     /** 选择Go信号流。 */
        EDITOR_SELECTION_Go_TEXT,
        EDITOR_SELECTION_Go_MARKOV_OPERATOR,
        EDITOR_SELECTION_Go_MARKOV_EQUIVALENT,
        EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE,
        EDITOR_SELECTION_Go_MARKOV_COMMON_CAUSE_2,
        EDITOR_SELECTION_Go_MARKOV_CHART,
        EDITOR_SELECTION_Go_SELECTION
    };
};

#endif // DEFINATIONEDITORSELECTIONTYPE_H
