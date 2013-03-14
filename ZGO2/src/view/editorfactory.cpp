#include "view/editorfactory.h"

/**
 * 生成编辑器的实例。
 * @return 编辑器，如果类别不存在返回空指针。
 */
void* EditorFactory::produce(qint32 type)
{
    EditorAbstract *editor = 0L;
    switch(type)
    {
    case TYPE_WELCOME:
        editor = new EditorWelcome();
        break;
    case TYPE_GO:
        editor = new EditorGO();
        break;
    }
    if (0L != editor)
    {
        editor->setId(this->id());
    }
    return editor;
}
