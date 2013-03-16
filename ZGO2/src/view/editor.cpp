#include "view/editor.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
Editor::Editor(QWidget *parent) : QWidget(parent), Messager()
{
    // 初始化TabWidget。
    this->tabWidget = new QTabWidget(this);
    this->tabWidget->setTabsClosable(true);
    this->connect(this->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tryCloseTab(int)));
    // 配置基本的布局。
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->tabWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    // 初始化工厂类和编辑器的集合。
    this->editors = new QVector<EditorAbstract*>();
    this->factory = new EditorFactory();
    EditorAbstract *editor = (EditorAbstract*)this->factory->produce(EditorFactory::TYPE_WELCOME);
    this->editors->push_back(editor);
    this->tabWidget->addTab(editor, editor->name());
    // 以下为测试用内容。
    editor = (EditorAbstract*)this->factory->produce(EditorFactory::TYPE_GO);
    this->editors->push_back(editor);
    this->tabWidget->addTab(editor, editor->name());
}

/**
 * 尝试保存所有文件。
 * @return 如果成功返回true，否则返回false。
 */
bool Editor::trySaveAll()
{
    for (int i = 0; i < this->editors->size(); ++i)
    {
        if (!this->editors->at(i)->trySave())
        {
            return false;
        }
    }
    return true;
}

/**
 * 尝试关闭所有文件。
 * @return 如果成功返回true，否则返回false。
 */
bool Editor::tryCloseAll()
{
    while (this->tabWidget->count() > 0)
    {
        if (!this->tryCloseTab(0))
        {
            return false;
        }
    }
    return true;
}

/**
 * 关闭指定的页面。
 * @param index 页面的索引。
 * @return 如果成功返回true，否则返回false。
 */
bool Editor::tryCloseTab(int index)
{
    if (this->editors->at(index)->tryClose())
    {
        this->editors->remove(index);
        this->tabWidget->removeTab(index);
        return true;
    }
    return false;
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void Editor::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    MessageFactoryMainWindow factory;
    controller->listen(factory.getMessageName(MessageFactoryMainWindow::MAINWINDOW_TRYCLOSE), this);
}

/**
 * 消息事件。
 * @param message 消息内容。
 */
void Editor::messageEvent(Message *message)
{
    MessageFactoryMainWindow factory;
    if (message->name() == factory.getMessageName(MessageFactoryMainWindow::MAINWINDOW_TRYCLOSE))
    {
        if (this->tryCloseAll())
        {
            this->sendMessage(factory.produce(MessageFactoryMainWindow::MAINWINDOW_CLOSE));
        }
    }
}
