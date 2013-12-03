#include "viewgo.h"
#include "messagefactory.h"
#include "editorgo.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ViewGO::ViewGO(QWidget *parent) : GraphicsView(parent)
{
    this->_editor = (EditorGO*)parent;
    this->_scene = new SceneGO(this);
    this->setScene(this->_scene);
}

ViewGO::~ViewGO()
{
    this->Messager::~Messager();
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

void ViewGO::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_ZOOM_IN:
        zoomIn();
        break;
    case MessageFactory::TYPE_EDITOR_ZOOM_OUT:
        zoomOut();
        break;
    default:
        this->_scene->messageEvent(message);
        break;
    }
}

void ViewGO::save(QDomDocument &document, QDomElement &root)
{
    this->_scene->save(document, root);
}

bool ViewGO::tryOpen(QDomElement &root)
{
    return this->_scene->tryOpen(root);
}

EditorGO* ViewGO::editor() const
{
    return this->_editor;
}
