#include <QDomDocument>
#include <QMessageBox>
#include "editorgo.h"
#include "gosignalfactory.h"
#include "messagefactory.h"
#include "definationtooltype.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorGO::EditorGO(QWidget *parent) : EditorAbstract(parent)
{
    this->_view = new ViewGO(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->_view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("GO Files(*.go)");
    this->_suffix = "go";
}

/**
 * Bind message.
 * @param controller The message controller.
 */
void EditorGO::bindMessage(MessageController *controller)
{
    this->EditorAbstract::bindMessage(controller);
    this->_view->bindMessage(controller);
}

void EditorGO::messageEvent(QSharedPointer<Message> message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY:
    case MessageFactory::TYPE_EDITOR_ANALYSIS_PATH:
    case MessageFactory::TYPE_EDITOR_ANALYSIS_CUT:
        if (this->modified())
        {
            if (!this->trySave())
            {
                return;
            }
        }
    }
    if (message->paramString == "")
    {
        message->paramString = this->path();
    }
    this->_view->messageEvent(message);
}

bool EditorGO::save()
{
    QDomDocument document;
    QDomElement root = document.createElement("GO_Project");
    root.setAttribute("support", "ZHG");
    document.appendChild(root);
    this->_view->save(document, root);
    QFile file(this->path());
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    file.write(document.toByteArray(4));
    file.flush();
    file.close();
    return true;
}

bool EditorGO::tryOpen(const QString path)
{
    QDomDocument document;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Can not read file."));
        return false;
    }
    if (!document.setContent(&file))
    {
        file.close();
        QMessageBox::critical(this, tr("Error"), tr("The file content is broken. "));
        return false;
    }
    file.close();
    QDomElement root = document.firstChildElement();
    if (root.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("The file content is broken. "));
        return false;
    }
    if (root.attribute("support") != "ZHG")
    {
        QMessageBox::critical(this, tr("Error"), tr("The file content is broken. "));
        return false;
    }
    QDomElement element = root.firstChildElement();
    if (document.isNull())
    {
        QMessageBox::critical(this, tr("Error"), tr("The file content is broken. "));
        return false;
    }
    if (!this->_view->tryOpen(element))
    {
        QMessageBox::critical(this, tr("Error"), tr("The file content is broken. "));
    }
    this->setModified(false);
    return true;
}

void EditorGO::activate()
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND;
    this->sendMessage(message);
}
