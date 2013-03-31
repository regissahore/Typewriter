#include "editorfactory.h"
#include "editorwelcome.h"
#include "editorgo.h"
#include "editorwebview.h"
#include "definationeditortype.h"

/**
 * 生成编辑器的实例。
 * @return 编辑器，如果类别不存在返回空指针。
 */
void* EditorFactory::produce(int type)
{
    EditorAbstract *editor = 0L;
    switch(type)
    {
    case DefinationEditorType::EDITOR_TYPE_WELCOME:
        editor = new EditorWelcome();
        editor->setType(DefinationEditorType::EDITOR_TYPE_WELCOME);
        break;
    case DefinationEditorType::EDITOR_TYPE_GO:
        editor = new EditorGO();
        editor->setType(DefinationEditorType::EDITOR_TYPE_GO);
        break;
    case DefinationEditorType::EDITOR_TYPE_WEBVIEW:
        editor = new EditorWebView();
        editor->setType(DefinationEditorType::EDITOR_TYPE_WEBVIEW);
        break;
    }
    if (0L != editor)
    {
        editor->setId(this->id());
    }
    return editor;
}
