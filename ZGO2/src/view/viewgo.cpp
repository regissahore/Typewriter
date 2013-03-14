#include "view/viewgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ViewGO::ViewGO(QWidget *parent) : GraphicsView(parent)
{
    this->_scene = new SceneGO(this);
    this->setScene(this->_scene);
}
