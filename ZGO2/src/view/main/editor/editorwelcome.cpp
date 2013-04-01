#include "editorwelcome.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorWelcome::EditorWelcome(QWidget *parent) : EditorAbstract(parent)
{
    this->setPath("Path");
    this->setName(tr("Welcome"));
    this->setModified(false);
}

bool EditorWelcome::trySave()
{
    return true;
}

bool EditorWelcome::trySaveAs()
{
    return true;
}

bool EditorWelcome::tryClose()
{
    return true;
}
