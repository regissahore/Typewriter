#include <QObject>
#include "toolgotext.h"
#include "itemgotext.h"
#include "message.h"
#include "messagefactory.h"
#include "scenego.h"
#include "dialogstringinput.h"
#include "definationtooltype.h"

ToolGOText::ToolGOText(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->_item = new ItemGOText();
    this->sceneGO()->addItem(this->_item);
    this->_finish = false;
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
}

ToolGOText::~ToolGOText()
{
    if (!this->_finish)
    {
        delete this->_item;
    }
}

void ToolGOText::activate()
{
    DialogStringInput *dialog = new DialogStringInput();
    dialog->setWindowTitle(QObject::tr("Text Tool"));
    dialog->setText(QObject::tr("Input text: "));
    if (dialog->exec() == QDialog::Accepted && dialog->stringInput()->text().length() > 0)
    {
        this->_item->setText(dialog->stringInput()->text());
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->_item->setPos(event->scenePos().x(), event->scenePos().y());
}

void ToolGOText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->_finish = true;
    // Set the tool.
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND;
    this->sceneGO()->sendMessage(message);
    // Set the selection.
    message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(this->_item);
    this->sceneGO()->sendMessage(message);
    this->_finish = true;
}
