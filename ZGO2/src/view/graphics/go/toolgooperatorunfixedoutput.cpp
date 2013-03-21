#include "toolgooperatorunfixedoutput.h"
#include "scenego.h"

ToolGOOperatorUnfixedOutput::ToolGOOperatorUnfixedOutput(SceneGO *sceneGO) : ToolGOOperator(sceneGO)
{
}

/**
 * Get the output number of the GO model.
 */
void ToolGOOperatorUnfixedOutput::getOutputNumber()
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
        MessageFactoryTool *factory = new MessageFactoryTool();
        MessageToolSelection *message = (MessageToolSelection*)factory->produce(MessageFactoryTool::TOOL_SELECTION);
        message->setType(DefinationToolType::TOOL_TYPE_COMMON_POINTER);
        this->sceneGO()->sendMessage(message);
        delete factory;
    }
}
