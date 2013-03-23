#include "scenego.h"
#include "messager.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "itemgosource.h"
#include "toolgofactory.h"
#include "messagefactory.h"
#include "definationeditorselectiontype.h"

/**
 * The constructor.
 * @parent The father object.
 */
SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent), Messager()
{
    this->_tool = 0L;
    this->selectTool(DefinationToolType::TOOL_TYPE_COMMON_POINTER);
}

/**
 * Destructor.
 */
SceneGO::~SceneGO()
{
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        int type = item->TypedItem::type();
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            delete (ItemGOOperator*)item;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            delete (ItemGOSignal*)item;
        }
        else
        {
            delete item;
        }
    }
}

/**
 * Listen to tool selection message.
 * @param controller The message controller.
 */
void SceneGO::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

/**
 * The message event.
 * @param message The detail of the message.
 */
void SceneGO::messageEvent(Message *message)
{
    switch (message->type())
    {
    case MessageFactory::TYPE_TOOL_SELECTION:
        this->selectTool(message->paramInt);
        break;
    }
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
                this->_tool->activate();
            }
        }
    }
    else
    {
        this->_tool = ToolGOFactory::produce(this, type);
        this->_tool->activate();
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
