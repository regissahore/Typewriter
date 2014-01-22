#include "DockToolbox.h"
#include "MessageFactory.h"
#include "ToolboxAbstract.h"
#include "EditorFactory.h"

DockToolbox::DockToolbox(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Toolbox"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_toolbox = 0L;
    this->setMinimumWidth(150);
}

DockToolbox::~DockToolbox()
{
    this->clear();
}

QSize DockToolbox::sizeHint() const
{
    return QSize(200, 200);
}

void DockToolbox::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_EDITOR_TYPE, this);
}

void DockToolbox::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_TYPE:
        this->setToolbox(message->paramInt);
        break;
    }
}

void DockToolbox::setToolbox(int editorType)
{
    int type = ToolboxFactory::TOOLBOX_TYPE_NULL;
    switch (editorType)
    {
    case EditorFactory::EDITOR_TYPE_Go:
        type = ToolboxFactory::TOOLBOX_TYPE_Go;
        break;
    case EditorFactory::EDITOR_TYPE_Go_MARKOV:
        type = ToolboxFactory::TOOLBOX_TYPE_Go_MARKOV;
        break;
    }
    bool flag = false;
    if (this->_toolbox)
    {
        if (this->_toolbox->type() != type)
        {
            flag = true; // 已经有工具但类别不同。
        }
    }
    else
    {
        flag = true; // 没有工具。
    }
    if (flag)
    {
        this->clear();
        this->_toolbox = ToolboxFactory::produce(type);
        if (this->_toolbox)
        {
            this->_toolbox->bindMessage(this->MessageCreator::_messageController);
            this->setWidget(this->_toolbox);
        }
    }
}

void DockToolbox::clear()
{
    if (this->_toolbox)
    {
        delete this->_toolbox;
        this->_toolbox = 0L;
    }
}
