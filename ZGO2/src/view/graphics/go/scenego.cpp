#include "scenego.h"

/**
 * The constructor.
 * @parent The father object.
 */
SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent), Messager()
{
    this->_tool = 0L;
    //以下为测试内容。
    ItemGOOperator *go = new ItemGOOperator();
    GOOperator *model = new GOOperator();
    model->setType(19);
    model->setId(627);
    model->setName("Medium");
    model->input()->setNumber(3);
    model->subInput()->setNumber(1);
    model->output()->setNumber(6);
    go->setModel(model);
    this->addItem(go);
    ItemGOSource  *go2 = new ItemGOSource();
    GOOperator *model2 = new GOOperator();
    model2->setType(7);
    model2->setId(2);
    model2->setName("Source");
    model2->output()->setNumber(3);
    go2->setModel(model2);
    go2->setPos(100, 100);
    this->addItem(go2);
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
                delete this->_tool;
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
}
