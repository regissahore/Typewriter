#include "editor.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
Editor::Editor(QWidget *parent) : QWidget(parent), Messager()
{
    // 初始化TabWidget。
    this->_tabWidget = new QTabWidget(this);
    this->_tabWidget->setTabsClosable(true);
    this->connect(this->_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tryCloseTab(int)));
    this->connect(this->_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentChange(int)));
    // 配置基本的布局。
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->_tabWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    // 初始化工厂类和编辑器的集合。
    this->_editors = new QVector<EditorAbstract*>();
    this->_factory = new EditorFactory();
    EditorAbstract *editor = (EditorAbstract*)this->_factory->produce(DefinationEditorType::EDITOR_TYPE_WELCOME);
    this->_editors->push_back(editor);
    this->_tabWidget->addTab(editor, editor->name());
    // 以下为测试用内容。
    editor = (EditorAbstract*)this->_factory->produce(DefinationEditorType::EDITOR_TYPE_GO);
    this->_editors->push_back(editor);
    this->_tabWidget->addTab(editor, editor->name());
    // 以上为测试用内容。
}

/**
 * 尝试保存所有文件。
 * @return 如果成功返回true，否则返回false。
 */
bool Editor::trySaveAll()
{
    for (int i = 0; i < this->_editors->size(); ++i)
    {
        if (!this->_editors->at(i)->trySave())
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
    while (this->_tabWidget->count() > 0)
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
    if (this->_editors->at(index)->tryClose())
    {
        this->_editors->remove(index);
        this->_tabWidget->removeTab(index);
        return true;
    }
    return false;
}

/**
 * 编辑器变动事件。
 * @param index 编辑器的索引。
 */
void Editor::currentChange(int index)
{
    MessageFactoryEditor factory;
    Message* message = factory.produce(MessageFactoryEditor::EDITOR_TYPE);
    if (this->_editors->size() > 0)
    {
        message->setMessage((void*)(*this->_editors)[index]);
        for (int i = 0; i < this->_editors->size(); ++i)
        {
            if (i == index)
            {
                this->_editors->at(index)->activate();
            }
            else
            {
                this->_editors->at(index)->inactivate();
            }
        }
    }
    this->sendMessage(message);
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
    // 如果已经有打开的tab则发送编辑器类别消息。
    currentChange(this->_tabWidget->currentIndex());
    for (int i = 0; i < this->_editors->size(); ++i)
    {
        this->_editors->at(i)->bindMessage(controller);
    }
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
