#include "ViewGo.h"
#include "MessageFactory.h"
#include "EditorGo.h"

ViewGo::ViewGo(QWidget *parent) : GraphicsView(parent)
{
    this->_editor = (EditorGo*)parent;
    this->_scene = new SceneGo(this);
    this->setScene(this->_scene);
}

ViewGo::~ViewGo()
{
    this->Messager::~Messager();
}

void ViewGo::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    this->_scene->bindMessage(controller);
}

void ViewGo::messageEvent(shared_ptr<Message> message)
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

void ViewGo::save(QDomDocument &document, QDomElement &root)
{
    this->_scene->save(document, root);
}

bool ViewGo::tryOpen(QDomElement &root)
{
    return this->_scene->tryOpen(root);
}

EditorGo* ViewGo::editor() const
{
    return this->_editor;
}
