#include "EditorAbstract.h"
#include "EditorFactory.h"
#include "EditorWelcome.h"
#include "EditorGo.h"
#include "EditorGoMarkov.h"
#include "EditorWebview.h"
#include "EditorGoMarkovChart.h"

EditorAbstract *EditorFactory::produce(int type)
{
    EditorAbstract *editor = 0L;
    switch(type)
    {
    case EDITOR_TYPE_WELCOME:
        editor = new EditorWelcome();
        break;
    case EDITOR_TYPE_GO:
        editor = new EditorGo();
        break;
    case EDITOR_TYPE_GO_MARKOV:
        editor = new EditorGoMarkov();
        break;
    case EDITOR_TYPE_WEBVIEW:
        editor = new EditorWebView();
        break;
    case EDITOR_TYPE_GO_MARKOV_CHART:
        editor = new EditorGoMarkovChart();
        break;
    }
    if (editor != 0L)
    {
        editor->setType(type);
    }
    return editor;
}
