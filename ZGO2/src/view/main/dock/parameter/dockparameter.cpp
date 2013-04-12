#include <QVBoxLayout>
#include "dockparameter.h"
#include "parameterabstract.h"
#include "messagefactory.h"
#include "itemdrawable.h"
#include "parameterfactory.h"

DockParameter::DockParameter(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Parameter"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_parameter = new ParameterAbstract(this);
    this->setWidget(this->_parameter);
}

void DockParameter::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_EDITOR_SELECTION, this);
}

void DockParameter::messageEvent(Message *message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_SELECTION:
        this->changeParameter((ItemDrawable*)message->message());
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
    this->setWidget(this->_parameter);
}
