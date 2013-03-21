#include "toolgooperatorunfixedinput.h"
#include "scenego.h"
#include "gooperatorfactory.h"
#include "gooperator.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorUnfixedInput::ToolGOOperatorUnfixedInput(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
}

/**
 * Activate.
 */
void ToolGOOperatorUnfixedInput::activate()
{
    this->getInputNumber();
}

/**
 * Get the input number of the GO model.
 */
void ToolGOOperatorUnfixedInput::getInputNumber()
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
        MessageFactoryTool *factory = new MessageFactoryTool();
        MessageToolSelection *message = (MessageToolSelection*)factory->produce(MessageFactoryTool::TOOL_SELECTION);
        message->setType(DefinationToolType::TOOL_TYPE_COMMON_POINTER);
        this->sceneGO()->sendMessage(message);
        delete factory;
    }
}
