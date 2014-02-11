#include <QVBoxLayout>
#include "DockParameter.h"
#include "ParameterAbstract.h"
#include "MessageFactory.h"
#include "ItemDrawable.h"
#include "ParameterFactory.h"
using namespace std;

DockParameter::DockParameter(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Parameter"));
    this->setFeatures(QDockWidget::DockWidgetMovable);
    this->_parameter = new ParameterAbstract(this);
    this->setWidget(this->_parameter);
}

DockParameter::~DockParameter()
{
    this->Messager::~Messager();
}

void DockParameter::bindMessage()
{
    this->listen(MessageFactory::TYPE_EDITOR_SELECTION);
    this->listen(MessageFactory::TYPE_EDITOR_TYPE);
}

void DockParameter::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_SELECTION:
        this->changeParameter((ItemDrawable*)message->message());
        break;
    case MessageFactory::TYPE_EDITOR_TYPE:
        this->changeParameter(nullptr);
        break;
    default:
        break;
    }
}

void DockParameter::changeParameter(ItemDrawable* item)
{
    delete this->_parameter;
    int type;
    if (item == nullptr)
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
