#include "editorwelcome.h"

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
