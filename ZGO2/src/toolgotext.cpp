#include <QObject>
#include "toolgotext.h"
#include "itemgotext.h"
#include "message.h"
#include "messagefactory.h"
#include "scenego.h"
#include "dialogstringinput.h"
#include "definationtooltype.h"
#include "viewgo.h"
#include "editorgo.h"

ToolGOText::ToolGOText(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
    this->_isActivated = false;
    this->_item = 0L;
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND;
}

ToolGOText::~ToolGOText()
{
    if (this->_item != 0L)
    {
        delete this->_item;
    }
}

void ToolGOText::activate(QGraphicsSceneMouseEvent *event)
{
    this->_isActivated = true;
    this->_item = new ItemGOText();
    this->sceneGO()->addItem(this->_item);
    DialogStringInput *dialog = new DialogStringInput();
    dialog->setWindowTitle(QObject::tr("Text Tool"));
    dialog->setText(QObject::tr("Input text: "));
    if (dialog->exec() == QDialog::Accepted && dialog->stringInput()->text().length() > 0)
    {
        this->_item->setText(dialog->stringInput()->text());
        this->_item->setPos(event->scenePos());
    }
    else
    {
        delete this->_item;
        this->_item = 0L;
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (this->_isActivated)
    {
        this->_item->setPos(event->scenePos());
    }
    else
    {
        this->activate(event);
    }
}

void ToolGOText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (event->button() == Qt::LeftButton)
    {
        this->sceneGO()->viewGO()->editor()->setModified(true);
        Message* message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_item);
        this->sceneGO()->sendMessage(message);
        this->activate(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOText::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
    }
}
