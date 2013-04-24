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
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
}

ToolGOText::~ToolGOText()
{
    delete this->_item;
}

void ToolGOText::activate()
{
    this->_item = new ItemGOText();
    this->sceneGO()->addItem(this->_item);
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
    if (event->button() == Qt::LeftButton)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_item);
        this->sceneGO()->sendMessage(message);
        this->activate();
    }
    else if (event->button() == Qt::RightButton)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOText::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOLTYPE_GO_POINTER_EXTEND;
        this->sceneGO()->sendMessage(message);
    }
}
