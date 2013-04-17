#include <QFileDialog>
#include "editor.h"
#include "messagefactory.h"
#include "editorabstract.h"

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
    EditorAbstract *editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_WELCOME);
    this->_editors->push_back(editor);
    this->_tabWidget->addTab(editor, editor->name());
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
    if (this->_editors->size() > 0)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_TYPE);
        message->paramInt = (*this->_editors)[index]->type();
        for (int i = 0; i < this->_editors->size(); ++i)
        {
            if (i == index)
            {
                this->_editors->at(i)->activate();
            }
            else
            {
                this->_editors->at(i)->inactivate();
            }
        }
        this->sendMessage(message);
    }
}

/**
 * 绑定消息。
 * @param controller 控制器。
 */
void Editor::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    controller->listen(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE, this);
    controller->listen(MessageFactory::TYPE_EDITOR_NEW, this);
    controller->listen(MessageFactory::TYPE_EDITOR_OPEN, this);
    controller->listen(MessageFactory::TYPE_EDITOR_OPEN_EXIST, this);
    controller->listen(MessageFactory::TYPE_EDITOR_CLOSE, this);
    controller->listen(MessageFactory::TYPE_EDITOR_CLOSEALL, this);
    controller->listen(MessageFactory::TYPE_EDITOR_SAVE, this);
    controller->listen(MessageFactory::TYPE_EDITOR_SAVEAS, this);
    controller->listen(MessageFactory::TYPE_EDITOR_SAVEALL, this);
    controller->listen(MessageFactory::TYPE_TOOL_SELECTION, this);
    controller->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY, this);
    controller->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH, this);
    controller->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT, this);
    // 如果已经有打开的tab则发送编辑器类别消息。
    currentChange(this->_tabWidget->currentIndex());
}

/**
 * 消息事件。
 * @param message 消息内容。
 */
void Editor::messageEvent(Message *message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_MAINWINDOW_TRYCLOSE:
        if (this->tryCloseAll())
        {
            this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_CLOSE));
        }
        break;
    case MessageFactory::TYPE_EDITOR_NEW:
        this->createNewTab(message->paramInt);
        break;
    case MessageFactory::TYPE_EDITOR_OPEN:
        this->tryOpen();
        break;
    case MessageFactory::TYPE_EDITOR_OPEN_EXIST:
        this->openExist(message->paramString);
        break;
    case MessageFactory::TYPE_EDITOR_CLOSE:
        this->tryCloseTab(this->_tabWidget->currentIndex());
        break;
    case MessageFactory::TYPE_EDITOR_CLOSEALL:
        this->tryCloseAll();
        break;
    case MessageFactory::TYPE_EDITOR_SAVE:
        if (this->_editors->size() > 0)
        {
            this->_editors->at(this->_tabWidget->currentIndex())->trySave();
            this->_tabWidget->setTabText(this->_tabWidget->currentIndex(), this->_editors->at(this->_tabWidget->currentIndex())->name());
        }
        break;
    case MessageFactory::TYPE_EDITOR_SAVEALL:
        for (int i = 0; i < this->_editors->size(); ++i)
        {
            this->_editors->at(i)->trySave();
            this->_tabWidget->setTabText(i, this->_editors->at(i)->name());
        }
        break;
    case MessageFactory::TYPE_EDITOR_SAVEAS:
        if (this->_editors->size() > 0)
        {
            this->_editors->at(this->_tabWidget->currentIndex())->trySaveAs();
            this->_tabWidget->setTabText(this->_tabWidget->currentIndex(), this->_editors->at(this->_tabWidget->currentIndex())->name());
        }
        break;
    default:
        if (this->_editors->size() > 0)
        {
            this->_editors->at(this->_tabWidget->currentIndex())->messageEvent(message);
        }
        break;
    }
}

/**
 * Create a new GO tab.
 */
void Editor::createNewTab(int type)
{
    EditorAbstract *editor = (EditorAbstract*)this->_factory->produce(type);
    editor->bindMessage(this->MessageCreator::_messageController);
    this->_editors->push_back(editor);
    this->_tabWidget->addTab(editor, editor->name());
    this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
}

/**
 * Try open a file the editor is able to edit.
 */
void Editor::tryOpen()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("GO Files(*.go *.gom);;HTML Files(*.html);;GO Chart(*.goc)"));
    if (filePath != "")
    {
        QString extension = "";
        for (int i = filePath.length() - 1; i >= 0; --i)
        {
            extension = filePath[i] + extension;
            if (filePath[i] == '.')
            {
                break;
            }
        }
        if (extension.compare(extension, ".go", Qt::CaseInsensitive) == 0)
        {
            EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_GO);
            if (editor->tryOpen(filePath))
            {
                editor->bindMessage(this->MessageCreator::_messageController);
                editor->setPath(filePath);
                this->_editors->push_back(editor);
                this->_tabWidget->addTab(editor, editor->name());
                this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
            }
        }
        else if (extension.compare(extension, ".gom", Qt::CaseInsensitive) == 0)
        {
            EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_GO_MARKOV);
            if (editor->tryOpen(filePath))
            {
                editor->bindMessage(this->MessageCreator::_messageController);
                editor->setPath(filePath);
                this->_editors->push_back(editor);
                this->_tabWidget->addTab(editor, editor->name());
                this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
            }
        }
        else if (extension.compare(extension, ".html", Qt::CaseInsensitive) == 0)
        {
            EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_WEBVIEW);
            editor->setPath(filePath);
            this->_editors->push_back(editor);
            this->_tabWidget->addTab(editor, editor->name());
            this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
        }
        else if (extension.compare(extension, ".goc", Qt::CaseInsensitive) == 0)
        {
            EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_GO_MARKOV_CHART);
            editor->setPath(filePath);
            editor->tryOpen(filePath);
            this->_editors->push_back(editor);
            this->_tabWidget->addTab(editor, editor->name());
            this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
        }
    }
}

void Editor::openExist(QString filePath)
{
    QString extension = "";
    for (int i = filePath.length() - 1; i >= 0; --i)
    {
        extension = filePath[i] + extension;
        if (filePath[i] == '.')
        {
            break;
        }
    }
    if (extension.compare(extension, ".html", Qt::CaseInsensitive) == 0)
    {
        EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_WEBVIEW);
        editor->setPath(filePath);
        editor->bindMessage(this->MessageCreator::_messageController);
        this->_editors->push_back(editor);
        this->_tabWidget->addTab(editor, editor->name());
        this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
    }
    else if (extension.compare(extension, ".goc", Qt::CaseInsensitive) == 0)
    {
        EditorAbstract* editor = (EditorAbstract*)this->_factory->produce(EditorFactory::EDITOR_TYPE_GO_MARKOV_CHART);
        editor->setPath(filePath);
        if (editor->tryOpen(filePath))
        {
            editor->bindMessage(this->MessageCreator::_messageController);
            this->_editors->push_back(editor);
            this->_tabWidget->addTab(editor, editor->name());
            this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
        }
        else
        {
            delete editor;
        }
    }
}
