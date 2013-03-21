#include "toolgooperatortype13.h"
#include "scenego.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOOperatorType13::ToolGOOperatorType13(SceneGO *sceneGO) : ToolGOOperatorUnfixedInput(sceneGO)
{
    this->_GOOperator = new ItemGOOperatorType13();
    this->_GOOperator->setVisible(false);
    this->graphicsScene()->addItem(this->_GOOperator);
    this->getInputNumber();
    this->getOutputNumber();
}

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
        MessageFactoryTool *factory = new MessageFactoryTool();
        MessageToolSelection *message = (MessageToolSelection*)factory->produce(MessageFactoryTool::TOOL_SELECTION);
        message->setType(DefinationToolType::TOOL_TYPE_COMMON_POINTER);
        this->sceneGO()->sendMessage(message);
        delete factory;
    }
}
