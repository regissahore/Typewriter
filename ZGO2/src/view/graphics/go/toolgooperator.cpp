#include "toolgooperator.h"
#include "scenego.h"
#include "messagefactory.h"
#include "dialogintegerinput.h"
#include "gooperator.h"
#include "goiomodel.h"

/**
 * Constructor. The protected variable _GOOperator should be initialized and added to the scene.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperator::ToolGOOperator(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->_GOOperator = 0;
    this->_finish = false;
}

/**
 * Delete the operator if the initial process is canceled.
 */
ToolGOOperator::~ToolGOOperator()
{
    if (this->_finish)
    {
        if (this->_GOOperator != 0L)
        {
            this->_GOOperator->setParentItem(0L);
            delete this->_GOOperator;
        }
    }
}

/**
 * Move the operator for a suitable position.
 * @param event Mouse event.
 */
void ToolGOOperator::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_GOOperator)
    {
        this->_GOOperator->setVisible(true);
        this->_GOOperator->setPos(event->scenePos().x(), event->scenePos().y());
    }
}

/**
 * Put down the operator and set tool to pointer.
 * @param event Mouse event.
 */
void ToolGOOperator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    // Set the tool.
    Message* message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
    message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_POINTER;
    this->sceneGO()->sendMessage(message);
    // Set the selection.
    message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(this->_GOOperator);
    this->sceneGO()->sendMessage(message);
    this->_finish = true;
}


/**
 * Get the input number of the GO model.
 */
void ToolGOOperator::getInputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Input Number"));
    dialog->setText(QObject::tr("The number of input: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GOOperator->model()->input()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->updateGraphic();
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_POINTER;
        this->sceneGO()->sendMessage(message);
    }
}


/**
 * Get the output number of the GO model.
 */
void ToolGOOperator::getOutputNumber()
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Output Number"));
    dialog->setText(QObject::tr("The number of output: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        this->_GOOperator->model()->output()->setNumber(dialog->integerInput()->value());
        this->_GOOperator->updateGraphic();
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOL_TYPE_COMMON_POINTER;
        this->sceneGO()->sendMessage(message);
    }
}
