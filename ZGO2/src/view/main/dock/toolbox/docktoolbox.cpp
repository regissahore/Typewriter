#include "docktoolbox.h"
#include "messagefactory.h"
#include "toolboxabstract.h"
#include "editorfactory.h"

/**
 * 构造函数。
 * @param parent 父窗体
 */
DockToolbox::DockToolbox(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Toolbox"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_toolbox = 0L;
    this->setMinimumWidth(150);
}

/**
 * 析构函数。
 */
DockToolbox::~DockToolbox()
{
    this->clear();
}

QSize DockToolbox::sizeHint() const
{
    return QSize(200, 200);
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void DockToolbox::bindMessage(MessageController *controller)
{
    controller->listen(MessageFactory::TYPE_EDITOR_TYPE, this);
}

/**
 * 消息事件。
 * @param message 消息。
 */
void DockToolbox::messageEvent(Message *message)
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
            this->_toolbox->bindMessage(this->MessageListener::_messageController);
            this->setWidget(this->_toolbox);
        }
    }
}

/**
 * 清除已有的工具。
 */
void DockToolbox::clear()
{
    if (this->_toolbox)
    {
        delete this->_toolbox;
        this->_toolbox = 0L;
    }
}
