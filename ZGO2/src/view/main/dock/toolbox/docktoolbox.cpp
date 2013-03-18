#include "docktoolbox.h"

/**
 * 构造函数。
 * @param parent 父窗体
 */
DockToolbox::DockToolbox(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Toolbox"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_toolbox = 0L;
}

/**
 * 析构函数。
 */
DockToolbox::~DockToolbox()
{
    this->clear();
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void DockToolbox::bindMessage(MessageController *controller)
{
    MessageFactoryEditor factory;
    controller->listen(factory.getMessageName(MessageFactoryEditor::EDITOR_TYPE), this);
}

/**
 * 消息事件。
 * @param message 消息。
 */
void DockToolbox::messageEvent(Message *message)
{
    MessageFactoryEditor editorFactory;
    int type = DefinationToolboxType::TOOLBOX_TYPE_NULL;
    if (message->name() == editorFactory.getMessageName(MessageFactoryEditor::EDITOR_TYPE))
    {
        if(message->message() != 0L)
        {
            EditorAbstract* editor = (EditorAbstract*)message->message();
            switch (editor->type())
            {
            case DefinationEditorType::EDITOR_TYPE_GO:
                type = DefinationToolboxType::TOOLBOX_TYPE_GO;
                break;
            }
        }
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
        ToolboxFactory *factory = new ToolboxFactory();
        this->_toolbox = (ToolboxAbstract*)factory->produce(type);
        delete factory;
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
