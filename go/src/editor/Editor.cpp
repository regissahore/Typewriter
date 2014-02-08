#include <QFileDialog>
#include "Editor.h"
#include "MessageFactory.h"
#include "EditorAbstract.h"
#include "GlobalConfig.h"
using namespace std;

Editor::Editor(QWidget *parent) : QWidget(parent), Messager()
{
    this->_tabWidget = new QTabWidget(this);
    this->_tabWidget->setTabsClosable(true);
    this->connect(this->_tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tryCloseTab(int)));
    this->connect(this->_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentChange(int)));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(this->_tabWidget);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    this->_editors = new QVector<EditorAbstract*>();
    this->_factory = new EditorFactory();
}

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

bool Editor::tryCloseTab(int index)
{
    if (this->_editors->size() > 0)
    {
        if (this->_editors->at(index)->tryClose())
        {
            this->_editors->remove(index);
            this->_tabWidget->removeTab(index);
            return true;
        }
    }
    return false;
}

void Editor::currentChange(int index)
{
    if (this->_editors->size() > 0)
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_TYPE);
        message->paramInt = (*this->_editors)[index]->type();
        this->send(message);
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
    }
    else
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_TYPE);
        message->paramInt = EditorFactory::EDITOR_TYPE_NULL;
        this->send(message);
    }
}

void Editor::bindMessage()
{
    this->listen(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE);
    this->listen(MessageFactory::TYPE_EDITOR_NEW);
    this->listen(MessageFactory::TYPE_EDITOR_OPEN);
    this->listen(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
    this->listen(MessageFactory::TYPE_EDITOR_CLOSE);
    this->listen(MessageFactory::TYPE_EDITOR_CLOSEALL);
    this->listen(MessageFactory::TYPE_EDITOR_SAVE);
    this->listen(MessageFactory::TYPE_EDITOR_SAVEAS);
    this->listen(MessageFactory::TYPE_EDITOR_SAVEALL);
    this->listen(MessageFactory::TYPE_TOOL_SELECTION);
    this->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY);
    this->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH);
    this->listen(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT);
    this->listen(MessageFactory::TYPE_EDITOR_COPY);
    this->listen(MessageFactory::TYPE_EDITOR_DELETE);
    this->listen(MessageFactory::TYPE_EDITOR_ZOOM_IN);
    this->listen(MessageFactory::TYPE_EDITOR_ZOOM_OUT);
    this->listen(MessageFactory::TYPE_EDITOR_SET_GLOBAL_FEEDBACK);
    this->listen(MessageFactory::TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK);
    this->listen(MessageFactory::TYPE_EDITOR_SHOW_PARAMETER);
    this->listen(MessageFactory::TYPE_EDITOR_HIDE_PARAMETER);
    currentChange(this->_tabWidget->currentIndex());
}

void Editor::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_MAINWINDOW_TRYCLOSE:
        if (this->tryCloseAll())
        {
            this->send(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_CLOSE));
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

void Editor::createNewTab(int type)
{
    EditorAbstract *editor = (EditorAbstract*)this->_factory->produce(type);
    this->_editors->push_back(editor);
    this->_tabWidget->addTab(editor, editor->name());
    this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
}

void Editor::tryOpen()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), GlobalConfig::getInstance()->lastestPath(), tr("Go Files(*.go *.gom *.html)"));
    if (filePath != "")
    {
        GlobalConfig::getInstance()->setLastestPath(QFileInfo(filePath).absolutePath());
        GlobalConfig::getInstance()->addLastestFile(QFileInfo(filePath).absoluteFilePath());
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
        this->_editors->push_back(editor);
        this->_tabWidget->addTab(editor, editor->name());
        this->_tabWidget->setCurrentIndex(this->_editors->size() - 1);
    }
}
