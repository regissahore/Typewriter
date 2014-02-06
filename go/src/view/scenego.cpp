#include <QUrl>
#include <QDateTime>
#include <QDesktopServices>
#include <QMessageBox>
#include "SceneGo.h"
#include "Messager.h"
#include "ItemGoOperator.h"
#include "ItemGoSignal.h"
#include "ItemGoText.h"
#include "GoOperator.h"
#include "ToolGoFactory.h"
#include "MessageFactory.h"
#include "DefinationEditorSelectionType.h"
#include "GoGraph.h"
#include "DefinationGoType.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "GoPathSetSetSet.h"
#include "GoCutSet.h"
#include "DialogIntegerInput.h"
#include "ItemEmpty.h"
#include "ViewGo.h"

SceneGo::SceneGo(QObject *parent) : QGraphicsScene(parent), Messager()
{
    this->_tool = 0L;
    this->_emptyTopLeft = new ItemEmpty();
    this->_emptyBottomRight = new ItemEmpty();
    this->addItem(this->_emptyTopLeft);
    this->addItem(this->_emptyBottomRight);
    this->_viewGo = (ViewGo*)parent;
}

SceneGo::~SceneGo()
{
    this->Messager::~Messager();
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        int type = item->TypedItem::type();
        if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            delete (ItemGoOperator*)item;
        }
        else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            delete (ItemGoSignal*)item;
        }
        else
        {
            delete item;
        }
    }
}

void SceneGo::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

void SceneGo::messageEvent(QSharedPointer<Message> message)
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

void SceneGo::save(QDomDocument &document, QDomElement &root)
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

bool SceneGo::tryOpen(QDomElement &root)
{
    if (root.tagName() != "scene")
    {
        return false;
    }
    bool flag = true;
    QList<ItemGoOperator*> operatorList;
    QList<ItemGoSignal*> signalList;
    for (auto element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "operator")
        {
            ItemGoOperator *item = new ItemGoOperator();
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
            ItemGoSignal *item = new ItemGoSignal();
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
            ItemGoText *item = new ItemGoText();
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

void SceneGo::selectTool(int type)
{
    if (this->_tool)
    {
        if (this->_tool->type() != type)
        {
            ToolGoAbstract *newTool = ToolGoFactory::produce(this, type);
            if (newTool != 0L)
            {
                delete this->_tool;
                this->_tool = newTool;
            }
        }
    }
    else
    {
        this->_tool = ToolGoFactory::produce(this, type);
    }
}

void SceneGo::keyPressEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyPressEvent(event);
    }
    this->QGraphicsScene::keyPressEvent(event);
}

void SceneGo::keyReleaseEvent(QKeyEvent *event)
{
    if (this->_tool)
    {
        this->_tool->keyReleaseEvent(event);
    }
    this->QGraphicsScene::keyReleaseEvent(event);
}

void SceneGo::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseDoubleClickEvent(event);
    }
    this->QGraphicsScene::mouseDoubleClickEvent(event);
}

void SceneGo::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseMoveEvent(event);
    }
    this->QGraphicsScene::mouseMoveEvent(event);
}

void SceneGo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mousePressEvent(event);
    }
    this->QGraphicsScene::mousePressEvent(event);
}

void SceneGo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->_tool)
    {
        this->_tool->mouseReleaseEvent(event);
    }
    this->extendEdge(event->scenePos().x(), event->scenePos().y());
    this->QGraphicsScene::mouseReleaseEvent(event);
}

GoGraph* SceneGo::generatorGoGraph()
{
    GoGraph *graph = new GoGraph();
    graph->bindMessage(this->MessageListener::_messageController);
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
        {
            ItemGoOperator *op = (ItemGoOperator*)item;
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
            graph->addOperator(((ItemGoOperator*)item)->model());
            break;
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL:
            ((ItemGoSignal*)item)->model()->setU(((ItemGoSignal*)item)->start()->op->model());
            switch (((ItemGoSignal*)item)->start()->type)
            {
            case DefinationGoType::GO_OPERATOR_INPUT:
                ((ItemGoSignal*)item)->start()->op->model()->input()->set(((ItemGoSignal*)item)->start()->index, ((ItemGoSignal*)item)->model());
                break;
            case DefinationGoType::GO_OPERATOR_SUBINPUT:
                ((ItemGoSignal*)item)->start()->op->model()->subInput()->set(((ItemGoSignal*)item)->start()->index, ((ItemGoSignal*)item)->model());
                break;
            case DefinationGoType::GO_OPERATOR_OUTPUT:
                ((ItemGoSignal*)item)->start()->op->model()->output()->addSignal(((ItemGoSignal*)item)->start()->index, ((ItemGoSignal*)item)->model());
                break;
            }
            ((ItemGoSignal*)item)->model()->setV(((ItemGoSignal*)item)->end()->op->model());
            switch (((ItemGoSignal*)item)->end()->type)
            {
            case DefinationGoType::GO_OPERATOR_INPUT:
                ((ItemGoSignal*)item)->end()->op->model()->input()->set(((ItemGoSignal*)item)->end()->index, ((ItemGoSignal*)item)->model());
                break;
            case DefinationGoType::GO_OPERATOR_SUBINPUT:
                ((ItemGoSignal*)item)->end()->op->model()->subInput()->set(((ItemGoSignal*)item)->end()->index, ((ItemGoSignal*)item)->model());
                break;
            case DefinationGoType::GO_OPERATOR_OUTPUT:
                ((ItemGoSignal*)item)->end()->op->model()->output()->addSignal(((ItemGoSignal*)item)->end()->index, ((ItemGoSignal*)item)->model());
                break;
            }
            graph->addSignal(((ItemGoSignal*)item)->model());
            break;
        default:
            break;
        }
    }
    return graph;
}

void SceneGo::analysisProbability(const QString filePath)
{
    GoGraph *graph = this->generatorGoGraph();
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

void SceneGo::analysisPath(const QString filePath)
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Set order"));
    dialog->setText(QObject::tr("Input path order: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        GoGraph *graph = this->generatorGoGraph();
        GoPathSetSetSet path = graph->findPath(dialog->integerInput()->value());
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

void SceneGo::analysisCut(const QString filePath)
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Set order"));
    dialog->setText(QObject::tr("Input cut order: "));
    dialog->integerInput()->setMinimum(1);
    if (dialog->exec() == QDialog::Accepted)
    {
        GoGraph *graph = this->generatorGoGraph();
        GoPathSetSetSet cut = graph->findCut(dialog->integerInput()->value());
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

void SceneGo::extendEdge(float x, float y)
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

ViewGo* SceneGo::viewGo() const
{
    return this->_viewGo;
}
