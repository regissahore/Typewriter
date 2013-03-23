#include "toolgooperatortype13.h"
#include "scenego.h"
#include "gooperator.h"
#include "messagefactory.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType13::ToolGOOperatorType13(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType13();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
}

/**
 * Activate.
 */
void ToolGOOperatorType13::activate()
{
    this->getInputNumber();
    this->getOutputNumber();
}

/**
 * Get the output number of the model.
 */
void ToolGOOperatorType13::getOutputNumber()
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
