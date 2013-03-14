#include "view/viewgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ViewGO::ViewGO(QWidget *parent) : View(parent)
{
    this->_scene = new SceneGO(this);
    this->view()->setScene(this->_scene);
}
