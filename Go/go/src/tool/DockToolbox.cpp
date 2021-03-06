#include "DockToolbox.h"
#include "MessageFactory.h"
#include "ToolboxAbstract.h"
#include "EditorFactory.h"
using namespace std;

DockToolbox::DockToolbox(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Toolbox"));
    this->setFeatures(QDockWidget::DockWidgetMovable);
    this->_toolbox = nullptr;
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

void DockToolbox::bindMessage()
{
    this->listen(MessageFactory::TYPE_EDITOR_TYPE);
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
    case EditorFactory::EDITOR_TYPE_GO:
        type = ToolboxFactory::TOOLBOX_TYPE_GO;
        break;
    case EditorFactory::EDITOR_TYPE_GO_MARKOV:
        type = ToolboxFactory::TOOLBOX_TYPE_GO_MARKOV;
        break;
    }
    bool flag = false;
    if (this->_toolbox)
    {
        if (this->_toolbox->type() != type)
        {
            flag = true;
        }
    }
    else
    {
        flag = true;
    }
    if (flag)
    {
        this->clear();
        this->_toolbox = ToolboxFactory::produce(type);
        if (this->_toolbox)
        {
            this->setWidget(this->_toolbox);
        }
    }
}

void DockToolbox::clear()
{
    if (this->_toolbox)
    {
        delete this->_toolbox;
        this->_toolbox = nullptr;
    }
}
