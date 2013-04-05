#include <QDomDocument>
#include "editorgo.h"
#include "gosignalfactory.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
EditorGO::EditorGO(QWidget *parent) : EditorAbstract(parent)
{
    this->view = new ViewGO(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("GO Files(*.go)");

    this->_savedOperatorID = 1;
    this->_savedSignalID = 1;
    this->activate();
}

/**
 * Bind message.
 * @param controller The message controller.
 */
void EditorGO::bindMessage(MessageController *controller)
{
    this->EditorAbstract::bindMessage(controller);
    this->view->bindMessage(controller);
}

void EditorGO::messageEvent(Message *message)
{
    if (message->paramString == "")
    {
        message->paramString = this->path();
    }
    this->view->messageEvent(message);
}

void EditorGO::activate()
{
    GOOperatorFactory::setID(this->_savedOperatorID);
    GOSignalFactory::setID(this->_savedSignalID);
}

void EditorGO::inactivate()
{
    this->_savedOperatorID = GOOperatorFactory::currentID();
    this->_savedSignalID = GOSignalFactory::currentID();
}

bool EditorGO::save()
{
    QDomDocument document;
    QDomElement root = document.createElement("GO_Project");
    root.setAttribute("support", "ZHG");
    document.appendChild(root);
    this->view->save(document, root);
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
        return false;
    }
    if (!document.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    QDomElement root = document.firstChildElement();
    if (root.isNull())
    {
        return false;
    }
    if (root.attribute("support") != "ZHG")
    {
        return false;
    }
    QDomElement element = root.firstChildElement();
    if (document.isNull())
    {
        return false;
    }
    if (!this->view->tryOpen(element))
    {
        return false;
    }
    this->setModified(false);
    return true;
}
