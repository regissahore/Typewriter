#include <QUrl>
#include <QDateTime>
#include <QDesktopServices>
#include <QMessageBox>
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
#include "goinput.h"
#include "gooutput.h"
#include "gopathsetsetset.h"
#include "gocutset.h"
#include "dialogintegerinput.h"
#include "itemempty.h"
#include "viewgo.h"

SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent), Messager()
{
    this->_tool = 0L;
    this->_emptyTopLeft = new ItemEmpty();
    this->_emptyBottomRight = new ItemEmpty();
    this->addItem(this->_emptyTopLeft);
    this->addItem(this->_emptyBottomRight);
    this->_viewGO = (ViewGO*)parent;
}

SceneGO::~SceneGO()
{
    this->Messager::~Messager();
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

void SceneGO::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

void SceneGO::messageEvent(QSharedPointer<Message> message)
{
    QKeyEvent *event = 0L;
    switch (message->type())
    {
    case MessageFactory::TYPE_TOOL_SELECTION:
        this->selectTool(message->paramInt);
        break;
    case MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY:
        this->analysisProbability(message->paramString);
        break;
    case MessageFactory::TYPE_EDITOR_ANALYSIS_PATH:
        this->analysisPath(message->paramString);
        break;
    case MessageFactory::TYPE_EDITOR_ANALYSIS_CUT:
        this->analysisCut(message->paramString);
        break;
    case MessageFactory::TYPE_EDITOR_COPY:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    case MessageFactory::TYPE_EDITOR_SET_GLOBAL_FEEDBACK:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_G, Qt::ControlModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    case MessageFactory::TYPE_EDITOR_UNSET_GLOBAL_FEEDBBACK:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_G, Qt::ControlModifier | Qt::ShiftModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    case MessageFactory::TYPE_EDITOR_DELETE:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    case MessageFactory::TYPE_EDITOR_SHOW_PARAMETER:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_P, Qt::ControlModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    case MessageFactory::TYPE_EDITOR_HIDE_PARAMETER:
        event = new QKeyEvent(QEvent::KeyRelease, Qt::Key_P, Qt::ControlModifier | Qt::ShiftModifier);
        this->_tool->keyReleaseEvent(event);
        break;
    default:
        break;
    }
    if (event != 0L)
    {
        delete event;
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
            item->setModelType(element.attribute("type").toInt());
            this->addItem(item);
            if (item->tryOpen(element))
            {
                operatorList.push_back(item);
            }
            else
            {
                flag = false;
                delete item;
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
                delete item;
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
            if (signalList[i]->start()->id == operatorList[j]->model()->realID())
            {
                signalList[i]->start()->op = operatorList[j];
                operatorList[j]->setSignal(signalList[i], signalList[i]->start()->type, signalList[i]->start()->index);
            }
            if (signalList[i]->end()->id == operatorList[j]->model()->realID())
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

void SceneGO::keyPressEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyPressEvent(event);
    }
    this->QGraphicsScene::keyPressEvent(event);
}

void SceneGO::keyReleaseEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyReleaseEvent(event);
    }
    this->QGraphicsScene::keyReleaseEvent(event);
}

void SceneGO::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseDoubleClickEvent(event);
    }
    this->QGraphicsScene::mouseDoubleClickEvent(event);
}

void SceneGO::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseMoveEvent(event);
    }
    this->QGraphicsScene::mouseMoveEvent(event);
}

void SceneGO::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mousePressEvent(event);
    }
    this->QGraphicsScene::mousePressEvent(event);
}

void SceneGO::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseReleaseEvent(event);
    }
    this->extendEdge(event->scenePos().x(), event->scenePos().y());
    this->QGraphicsScene::mouseReleaseEvent(event);
}

GOGraph* SceneGO::generatorGOGraph()
{
    GOGraph *graph = new GOGraph();
    graph->bindMessage(this->MessageListener::_messageController);
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGOOperator *op = (ItemGOOperator*)item;
            for (int j = 0; j < op->model()->output()->number(); ++j)
            {
                op->model()->output()->signal()->at(j)->clear();
            }
        }
    }
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
                ((ItemGOSignal*)item)->start()->op->model()->output()->addSignal(((ItemGOSignal*)item)->start()->index, ((ItemGOSignal*)item)->model());
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
                ((ItemGOSignal*)item)->end()->op->model()->output()->addSignal(((ItemGOSignal*)item)->end()->index, ((ItemGOSignal*)item)->model());
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

void SceneGO::analysisProbability(const QString filePath)
{
    GOGraph *graph = this->generatorGOGraph();
    graph->calcAccumulativeProbability();
    if (graph->getErrorMessage() == "")
    {
        graph->saveAsHTML(filePath + ".html");
        QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
        message->paramString = filePath + ".html";
        this->sendMessage(message);
    }
    else
    {
        QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
    }
    delete graph;
}

void SceneGO::analysisPath(const QString filePath)
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Set order"));
    dialog->setText(QObject::tr("Input path order: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        GOGraph *graph = this->generatorGOGraph();
        GOPathSetSetSet path = graph->findPath(dialog->integerInput()->value());
        path = graph->findPath(dialog->integerInput()->value());
        if (graph->getErrorMessage() == "")
        {
            graph->saveAsHTML(filePath + ".path.html", path);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
            message->paramString = filePath + ".path.html";
            this->sendMessage(message);
        }
        else
        {
            QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
        }
        delete graph;
    }
    delete dialog;
}

void SceneGO::analysisCut(const QString filePath)
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Set order"));
    dialog->setText(QObject::tr("Input cut order: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        GOGraph *graph = this->generatorGOGraph();
        GOPathSetSetSet cut = graph->findCut(dialog->integerInput()->value());
        if (graph->getErrorMessage() == "")
        {
            graph->saveAsHTML(filePath + ".cut.html", cut);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
            message->paramString = filePath + ".cut.html";
            this->sendMessage(message);
        }
        else
        {
            QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
        }
        delete graph;
    }
    delete dialog;
}

void SceneGO::extendEdge(float x, float y)
{
    float extendStep = 200;
    if (x - extendStep < this->_emptyTopLeft->x())
    {
        this->_emptyTopLeft->setX(x - extendStep);
    }
    if (y - extendStep < this->_emptyTopLeft->y())
    {
        this->_emptyTopLeft->setY(y - extendStep);
    }
    if (x + extendStep > this->_emptyBottomRight->x())
    {
        this->_emptyBottomRight->setX(x + extendStep);
    }
    if (y + extendStep > this->_emptyBottomRight->y())
    {
        this->_emptyBottomRight->setY(y + extendStep);
    }
}

ViewGO* SceneGO::viewGO() const
{
    return this->_viewGO;
}
