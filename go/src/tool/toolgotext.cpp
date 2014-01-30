#include <QObject>
#include "ToolGoText.h"
#include "ItemGoText.h"
#include "Message.h"
#include "MessageFactory.h"
#include "SceneGo.h"
#include "DialogStringInput.h"
#include "DefinationToolType.h"
#include "ViewGo.h"
#include "EditorGo.h"

ToolGoText::ToolGoText(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
    this->_isActivated = false;
    this->_item = 0L;
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND;
}

ToolGoText::~ToolGoText()
{
    if (this->_item != 0L)
    {
        delete this->_item;
    }
}

void ToolGoText::activate(QGraphicsSceneMouseEvent *event)
{
    this->_isActivated = true;
    this->_item = new ItemGoText();
    this->sceneGo()->addItem(this->_item);
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
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->sendMessage(message);
    }
}

void ToolGoText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

void ToolGoText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                               ((int)event->scenePos().y() / 10) * 10));
    if (event->button() == Qt::LeftButton)
    {
        this->sceneGo()->viewGo()->editor()->setModified(true);
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_item);
        this->sceneGo()->sendMessage(message);
        this->activate(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->sendMessage(message);
    }
}

void ToolGoText::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->sendMessage(message);
    }
}
