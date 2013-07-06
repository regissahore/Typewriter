#include "toolgooperator.h"
#include "scenego.h"
#include "messagefactory.h"
#include "dialogintegerinput.h"
#include "gooperator.h"
#include "gooperatorfactory.h"
#include "goinput.h"
#include "gooutput.h"
#include "definationeditorselectiontype.h"

/**
 * Constructor. The protected variable _GOOperator should be initialized and added to the scene.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperator::ToolGOOperator(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setCursor(Qt::SizeAllCursor);
    this->_isActivated = false;
    this->_GOOperator = 0L;
    this->_defaultToolType = DefinationToolType::TOOL_TYPE_GO_POINTER_EXTEND;
}

/**
 * Delete the operator if the initial process is canceled.
 */
ToolGOOperator::~ToolGOOperator()
{
    if (this->_GOOperator != 0L)
    {
        delete this->_GOOperator;
    }
}

void ToolGOOperator::setType(const int type)
{
    this->TypedItem::setType(type);
    this->_GOOperator = new ItemGOOperator();
    switch (this->type())
    {
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_1:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_1);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_2:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_2);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_3:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_3);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_4:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_4);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_5:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_5);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_6:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_6);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_7:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_7);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_8:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_8);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_9:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_9);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_10:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_10);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_11:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_11);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_12:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_12);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_13:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_13);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_14:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_14);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_15:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_15);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_16:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_16);
        break;
    case DefinationToolType::TOOL_TYPE_GO_OPERATOR_17:
        this->_GOOperator->setModelType(GOOperatorFactory::Operator_Type_17);
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
            ItemGOOperator *op = (ItemGOOperator*)item;
            visit[op->model()->id()] = true;
        }
    }
    for (int i = 1; i <= items.size() + 1; ++i)
    {
        if (!visit[i])
        {
            this->_GOOperator->model()->setId(i);
            break;
        }
    }
    this->graphicsScene()->addItem(this->_GOOperator);
}

void ToolGOOperator::activate(QGraphicsSceneMouseEvent *event)
{
    this->_isActivated = true;
    this->_GOOperator->setPos(event->scenePos());
    switch (this->_GOOperator->model()->type())
    {
    case GOOperatorFactory::Operator_Type_2:
        this->getInputNumber();
        break;
    case GOOperatorFactory::Operator_Type_4:
        this->getOutputNumber();
        break;
    case GOOperatorFactory::Operator_Type_10:
        this->getInputNumber();
        break;
    case GOOperatorFactory::Operator_Type_11:
        this->getInputNumber();
        break;
    case GOOperatorFactory::Operator_Type_13:
        if (this->getInputNumber())
        {
            this->getOutputNumber();
        }
        break;
    case GOOperatorFactory::Operator_Type_14:
        this->getInputNumber();
        break;
    default:
        break;
    }
}

/**
 * Move the operator for a suitable position.
 * @param event Mouse event.
 */
void ToolGOOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_isActivated)
    {
        this->_GOOperator->setVisible(true);
        this->_GOOperator->setPos(event->scenePos().x(), event->scenePos().y());
    }
    else
    {
        this->activate(event);
    }
}

/**
 * Put down the operator and set tool to pointer.
 * @param event Mouse event.
 */
void ToolGOOperator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Message* message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(this->_GOOperator);
        this->sceneGO()->sendMessage(message);
        this->setType(this->TypedItem::type());
        this->activate(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOOperator::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
    }
}


/**
 * Get the input number of the GO model.
 */
bool ToolGOOperator::getInputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Input Number"));
    dialog->setText(QObject::tr("The number of input: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GOOperator->model()->input()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->setModel(this->_GOOperator->model());
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
        return false;
    }
    return true;
}


/**
 * Get the output number of the GO model.
 */
bool ToolGOOperator::getOutputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Output Number"));
    dialog->setText(QObject::tr("The number of output: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GOOperator->model()->output()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->setModel(this->_GOOperator->model());
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
        return false;
    }
    return true;
}

bool ToolGOOperator::getDualNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Input and Output Number"));
    dialog->setText(QObject::tr("The number of input and output: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GOOperator->model()->input()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->model()->output()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->setModel(this->_GOOperator->model());
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = this->_defaultToolType;
        this->sceneGO()->sendMessage(message);
        return false;
    }
    return true;
}
