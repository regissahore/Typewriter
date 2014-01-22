#include <QVBoxLayout>
#include "DockParameter.h"
#include "ParameterAbstract.h"
#include "MessageFactory.h"
#include "ItemDrawable.h"
#include "ParameterFactory.h"

DockParameter::DockParameter(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Parameter"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_parameter = new ParameterAbstract(this);
    this->setWidget(this->_parameter);
}

DockParameter::~DockParameter()
{
    this->MessageListener::~MessageListener();
}

void DockParameter::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_EDITOR_SELECTION, this);
    controller->listen(MessageFactory::TYPE_EDITOR_TYPE, this);
}

void DockParameter::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_SELECTION:
        this->changeParameter((ItemDrawable*)message->message());
        break;
    case MessageFactory::TYPE_EDITOR_TYPE:
        this->changeParameter(0L);
        break;
    default:
        break;
    }
}

void DockParameter::changeParameter(ItemDrawable* item)
{
    delete this->_parameter;
    int type;
    if (item == 0L)
    {
        type = -1;
    }
    else
    {
        type = item->TypedItem::type();
    }
    this->_parameter = ParameterFactory::produce(type);
    this->_parameter->bindItem(item);
    this->_parameter->bindMessage(this->MessageCreator::_messageController);
    this->setWidget(this->_parameter);
}
