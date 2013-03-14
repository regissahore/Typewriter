#include "view/editorwelcome.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorWelcome::EditorWelcome(QWidget *parent) : EditorAbstract(parent)
{
    this->setName(tr("Welcome"));
    this->setPath("Path");
    this->setModified(false);
}
