#include "toolgooperator.h"
#include "scenego.h"

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
    MessageFactoryTool *factoryTool = new MessageFactoryTool();
    MessageToolSelection *messageToolSelection = (MessageToolSelection*)factoryTool->produce(MessageFactoryTool::TOOL_SELECTION);
    messageToolSelection->setType(DefinationToolType::TOOL_TYPE_COMMON_POINTER);
    this->sceneGO()->sendMessage(messageToolSelection);
    delete factoryTool;
    // Set the selection.
    MessageFactoryEditor *factoryEditor = new MessageFactoryEditor();
    MessageEditorSelection *messageEditorSelection = (MessageEditorSelection*)factoryEditor->produce(MessageFactoryEditor::EDITOR_SELECTION);
    messageEditorSelection->setMessage(this->_GOOperator);
    this->sceneGO()->sendMessage(messageEditorSelection);
    delete factoryEditor;
    this->_finish = true;
}
