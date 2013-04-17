#include "editorabstract.h"
#include "editorfactory.h"
#include "editorwelcome.h"
#include "editorgo.h"
#include "editorgomarkov.h"
#include "editorwebview.h"
#include "editorgomarkovchart.h"
#include "definationeditortype.h"

/**
 * 生成编辑器的实例。
 * @return 编辑器，如果类别不存在返回空指针。
 */
EditorAbstract *EditorFactory::produce(int type)
{
    EditorAbstract *editor = 0L;
    switch(type)
    {
    case EDITOR_TYPE_WELCOME:
        editor = new EditorWelcome();
        break;
    case EDITOR_TYPE_GO:
        editor = new EditorGO();
        break;
    case EDITOR_TYPE_GO_MARKOV:
        editor = new EditorGOMarkov();
        break;
    case EDITOR_TYPE_WEBVIEW:
        editor = new EditorWebView();
        break;
    case EDITOR_TYPE_GO_MARKOV_CHART:
        editor = new EditorGOMarkovChart();
        break;
    }
    if (editor != 0L)
    {
        editor->setType(type);
    }
    return editor;
}
