#include "scenego.h"
#include "messager.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "itemgotext.h"
#include "gooperator.h"
#include "toolgofactory.h"
#include "messagefactory.h"
#include "definationeditorselectiontype.h"
#include "gograph.h"
#include "definationgotype.h"
#include "goiomodel.h"

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

void SceneGO::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("scene");
    QList<QGraphicsItem*> items = this->items();
    root.appendChild(element);
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        item->save(document, element);
    }
}

bool SceneGO::tryOpen(QDomElement &root)
{
    if (root.tagName() != "scene")
    {
        return false;
    }
    bool flag = true;
    QList<ItemGOOperator*> operatorList;
    QList<ItemGOSignal*> signalList;
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "operator")
        {
            ItemGOOperator *item = new ItemGOOperator();
            item->setOperatorType(element.attribute("type").toInt());
            this->addItem(item);
            if (item->tryOpen(element))
            {
                operatorList.push_back(item);
            }
            else
            {
                flag = false;
                this->removeItem(item);
            }
        }
        else if (element.tagName() == "signal")
        {
            ItemGOSignal *item = new ItemGOSignal();
            this->addItem(item);
            if (item->tryOpen(element))
            {
                signalList.push_back(item);
            }
            else
            {
                flag = false;
                this->removeItem(item);
            }
        }
        else if (element.tagName() == "text")
        {
            ItemGOText *item = new ItemGOText();
            if (item->tryOpen(element))
            {
                this->addItem(item);
            }
        }
    }
    for (int i = 0; i < signalList.size(); ++i)
    {
        for (int j = 0; j < operatorList.size(); ++j)
        {
            if (signalList[i]->start()->id == operatorList[j]->model()->id())
            {
                signalList[i]->start()->op = operatorList[j];
                operatorList[j]->setSignal(signalList[i], signalList[i]->start()->type, signalList[i]->start()->index);
            }
            if (signalList[i]->end()->id == operatorList[j]->model()->id())
            {
                signalList[i]->end()->op = operatorList[j];
                operatorList[j]->setSignal(signalList[i], signalList[i]->end()->type, signalList[i]->end()->index);
            }
            if (signalList[i]->start()->op != 0L && signalList[i]->end()->op != 0L)
            {
                break;
            }
        }
        signalList[i]->updatePosition();
    }
    operatorList.clear();
    signalList.clear();
    return flag;
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

/**
 * Generate a GO graph based on the current scene.
 * @return The GO graph.
 */
GOGraph* SceneGO::generatorGOGraph()
{
    GOGraph *graph = new GOGraph();
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        switch (item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR:
            graph->addOperator(((ItemGOOperator*)item)->model());
            break;
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
            ((ItemGOSignal*)item)->model()->setU(((ItemGOSignal*)item)->start()->op->model());
            switch (((ItemGOSignal*)item)->start()->type)
            {
            case DefinationGOType::GO_OPERATOR_INPUT:
                ((ItemGOSignal*)item)->start()->op->model()->input()->set(((ItemGOSignal*)item)->start()->index, ((ItemGOSignal*)item)->model());
                break;
            case DefinationGOType::GO_OPERATOR_SUBINPUT:
                ((ItemGOSignal*)item)->start()->op->model()->subInput()->set(((ItemGOSignal*)item)->start()->index, ((ItemGOSignal*)item)->model());
                break;
            case DefinationGOType::GO_OPERATOR_OUTPUT:
                ((ItemGOSignal*)item)->start()->op->model()->output()->set(((ItemGOSignal*)item)->start()->index, ((ItemGOSignal*)item)->model());
                break;
            }
            ((ItemGOSignal*)item)->model()->setV(((ItemGOSignal*)item)->end()->op->model());
            switch (((ItemGOSignal*)item)->end()->type)
            {
            case DefinationGOType::GO_OPERATOR_INPUT:
                ((ItemGOSignal*)item)->end()->op->model()->input()->set(((ItemGOSignal*)item)->end()->index, ((ItemGOSignal*)item)->model());
                break;
            case DefinationGOType::GO_OPERATOR_SUBINPUT:
                ((ItemGOSignal*)item)->end()->op->model()->subInput()->set(((ItemGOSignal*)item)->end()->index, ((ItemGOSignal*)item)->model());
                break;
            case DefinationGOType::GO_OPERATOR_OUTPUT:
                ((ItemGOSignal*)item)->end()->op->model()->output()->set(((ItemGOSignal*)item)->end()->index, ((ItemGOSignal*)item)->model());
                break;
            }
            graph->addSignal(((ItemGOSignal*)item)->model());
            break;
        default:
            break;
        }
    }
    return graph;
}
