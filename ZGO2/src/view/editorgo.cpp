#include "view/editorgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorGO::EditorGO(QWidget *parent) : EditorAbstract(parent)
{
    this->view = new QGraphicsView(this);
}
