#include "scenego.h"

/**
 * The constructor.
 * @parent The father object.
 */
SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent), Messager()
{
    this->_tool = 0L;
}

/**
 * Listen to tool selection message.
 * @param controller The message controller.
 */
void SceneGO::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    MessageFactoryTool *factory = new MessageFactoryTool();
    controller->listen(factory->getMessageName(MessageFactoryTool::TOOL_SELECTION), this);
    delete factory;
}

/**
 * The message event.
 * @param message The detail of the message.
 */
void SceneGO::messageEvent(Message *message)
{
    MessageFactoryTool *factory = new MessageFactoryTool();
    if (message->name() == factory->getMessageName((MessageFactoryTool::TOOL_SELECTION)))
    {
        int toolType = ((MessageToolSelection*)message)->type();
        this->selectTool(toolType);
    }
    delete factory;
}

/**
 * Select the type of the tool.
 * @param The type of tool. @see DefinationToolType
 */
void SceneGO::selectTool(int type)
{
    if (this->_tool)
    {
        if (this->_tool->type() != type)
        {
            ToolGOAbstract *newTool = ToolGOFactory::produce(this, type);
            if (newTool != 0L)
            {
                ToolGOFactory::release(this->_tool);
                this->_tool = newTool;
            }
        }
    }
    else
    {
        this->_tool = ToolGOFactory::produce(this, type);
    }
}

/**
 * Key press event.
 * @param event Key event.
 */
void SceneGO::keyPressEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyPressEvent(event);
    }
    this->QGraphicsScene::keyPressEvent(event);
}

/**
 * Key release event.
 * @param event Key event.
 */
void SceneGO::keyReleaseEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyReleaseEvent(event);
    }
    this->QGraphicsScene::keyReleaseEvent(event);
}

/**
 * Mouse double click event.
 * @param event Mouse event.
 */
void SceneGO::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseDoubleClickEvent(event);
    }
    this->QGraphicsScene::mouseDoubleClickEvent(event);
}

/**
 * Mouse move event.
 * @param event Mouse event.
 */
void SceneGO::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseMoveEvent(event);
    }
    this->QGraphicsScene::mouseMoveEvent(event);
}

/**
 * Mouse press event.
 * @param event Mouse event.
 */
void SceneGO::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mousePressEvent(event);
    }
    this->QGraphicsScene::mousePressEvent(event);
}

/**
 * Mouse release event.
 * @param event Mouse event.
 */
void SceneGO::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseReleaseEvent(event);
    }
    this->QGraphicsScene::mouseReleaseEvent(event);
}
