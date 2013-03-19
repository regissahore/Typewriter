#include "viewgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ViewGO::ViewGO(QWidget *parent) : GraphicsView(parent)
{
    this->_scene = new SceneGO(this);
    this->setScene(this->_scene);
}

/**
 * Bind message listener to controller.
 * @param controller The message controller.
 */
void ViewGO::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    this->_scene->bindMessage(controller);
}
