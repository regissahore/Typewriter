#include "ToolGoOperator.h"
#include "SceneGo.h"
#include "MessageFactory.h"
#include "DialogIntegerInput.h"
#include "GoOperator.h"
#include "GoOperatorFactory.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "DefinationEditorSelectionType.h"
#include "ViewGo.h"
#include "EditorGo.h"

ToolGoOperator::ToolGoOperator(SceneGo *sceneGo) : ToolGoAbstract(sceneGo)
{
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
    this->_isActivated = false;
    this->_GoOperator = nullptr;
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND;
}

ToolGoOperator::~ToolGoOperator()
{
    if (this->_GoOperator != nullptr)
    {
        delete this->_GoOperator;
    }
}

void ToolGoOperator::setType(const int type)
{
    this->TypedItem::setType(type);
    this->_GoOperator = new ItemGoOperator();
    switch (this->type())
    {
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_3);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_4);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_5);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_6);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_7);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_8);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_9);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_10);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_11);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_12);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_13);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_14);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_15);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_16);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        this->_GoOperator->setModelType(GoOperatorFactory::Operator_Type_17);
        break;
    }
    QList<QGraphicsItem*> items = this->graphicsScene()->items();

    QVector<bool> visit;
    for (int i = 0; i <= items.size() + 1; ++i)
    {
        visit.push_back(false);
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
            visit[op->model()->id()] = true;
        }
    }
    for (int i = 1; i <= items.size() + 1; ++i)
    {
        if (!visit[i])
        {
            this->_GoOperator->model()->setId(i);
            break;
        }
    }

    visit.clear();
    for (int i = 0; i <= items.size() + 1; ++i)
    {
        visit.push_back(false);
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable* item = (ItemDrawable*)items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
            visit[op->model()->realID()] = true;
        }
    }
    for (int i = 1; i <= items.size() + 1; ++i)
    {
        if (!visit[i])
        {
            this->_GoOperator->model()->setRealID(i);
            break;
        }
    }

    this->graphicsScene()->addItem(this->_GoOperator);
}

void ToolGoOperator::activate(QGraphicsSceneMouseEvent *event)
{
    if (this->_isActivated)
    {
        this->setType(this->TypedItem::type());
    }
    this->_isActivated = true;
    this->_GoOperator->setPos(event->scenePos());
    switch (this->_GoOperator->model()->type())
    {
    case GoOperatorFactory::Operator_Type_2:
        this->getInputNumber();
        break;
    case GoOperatorFactory::Operator_Type_4:
        this->getOutputNumber();
        break;
    case GoOperatorFactory::Operator_Type_10:
        this->getInputNumber();
        break;
    case GoOperatorFactory::Operator_Type_11:
        this->getInputNumber();
        break;
    case GoOperatorFactory::Operator_Type_13:
        if (this->getInputNumber())
        {
            this->getOutputNumber();
        }
        break;
    case GoOperatorFactory::Operator_Type_14:
        this->getInputNumber();
        break;
    default:
        break;
    }
}

void ToolGoOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_GoOperator != nullptr)
    {
        event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                                   ((int)event->scenePos().y() / 10) * 10));
        if (this->_isActivated)
        {
            this->_GoOperator->setVisible(true);
            this->_GoOperator->setPos(event->scenePos().x(), event->scenePos().y());
        }
        else
        {
            this->activate(event);
        }
    }
}

void ToolGoOperator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_GoOperator != nullptr)
    {
        event->setScenePos(QPointF(((int)event->scenePos().x() / 10) * 10,
                                   ((int)event->scenePos().y() / 10) * 10));
        if (event->button() == Qt::LeftButton)
        {
            this->sceneGo()->viewGo()->editor()->setModified(true);
            this->activate(event);
        }
        else if (event->button() == Qt::RightButton)
        {
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
            message->paramInt = this->_defaultToolType;
            this->sceneGo()->send(message);
        }
    }
}

void ToolGoOperator::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (this->_GoOperator != nullptr)
        {
            delete this->_GoOperator;
            this->_GoOperator = nullptr;
        }
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->send(message);
    }
}


bool ToolGoOperator::getInputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput(this->sceneGo()->viewGo()->editor());
    dialog->setWindowTitle(QObject::tr("Input Number"));
    dialog->setText(QObject::tr("The number of input: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GoOperator->model()->input()->setNumber(dialog->integerInput()->value());
        this->_GoOperator->setModel(this->_GoOperator->model());
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_GoOperator);
        this->sceneGo()->send(message);
    }
    else
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->send(message);
        return false;
    }
    return true;
}


bool ToolGoOperator::getOutputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput(this->sceneGo()->viewGo()->editor());
    dialog->setWindowTitle(QObject::tr("Output Number"));
    dialog->setText(QObject::tr("The number of output: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GoOperator->model()->output()->setNumber(dialog->integerInput()->value());
        this->_GoOperator->setModel(this->_GoOperator->model());
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_GoOperator);
        this->sceneGo()->send(message);
    }
    else
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->send(message);
        return false;
    }
    return true;
}

bool ToolGoOperator::getDualNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput(this->sceneGo()->viewGo()->editor());
    dialog->setWindowTitle(QObject::tr("Input and Output Number"));
    dialog->setText(QObject::tr("The number of input and output: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GoOperator->model()->input()->setNumber(dialog->integerInput()->value());
        this->_GoOperator->model()->output()->setNumber(dialog->integerInput()->value());
        this->_GoOperator->setModel(this->_GoOperator->model());
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_GoOperator);
        this->sceneGo()->send(message);
    }
    else
    {
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGo()->send(message);
        return false;
    }
    return true;
}
