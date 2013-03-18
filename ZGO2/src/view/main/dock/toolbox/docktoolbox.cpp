#include "docktoolbox.h"

/**
 * 构造函数。
 * @param parent 父窗体
 */
DockToolbox::DockToolbox(QWidget *parent) : QDockWidget(parent), Messager()
{
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
    MessageFactory editorFactory;
    if (message->name() == editorFactory.getMessageName(MessageFactoryEditor::EDITOR_TYPE))
    {
        if (0L == message)
        {
            // 不显示
        }
        else
        {
            EditorAbstract* editor = (EditorAbstract*)message->message();
            switch (editor->type())
            {
            case DefinationEditorType::EDITOR_TYPE_WELCOME:
                break;
            case DefinationEditorType::EDITOR_TYPE_GO:
                break;
            default:
                break;
            }
        }
    }
}
