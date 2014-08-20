#include <cstdio>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include "SceneGoMarkov.h"
#include "ItemGoMarkovOperator.h"
#include "ItemGoSignal.h"
#include "ItemGoText.h"
#include "GoMarkovOperator.h"
#include "GoMarkovGraph.h"
#include "DefinationEditorSelectionType.h"
#include "DefinationGoType.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "ItemGoMarkovEquivalent.h"
#include "DefinationToolType.h"
#include "DialogGoMarkovPeriod.h"
#include "MessageFactory.h"
#include "GoMarkovChartData.h"
#include "GoMarkovEquivalent.h"
#include "ItemGoMarkovCommonCause.h"
#include "GoMarkovCommonCause.h"
#include "DialogIntegerInput.h"
#include "GoPathSetSetSet.h"
#include "DialogGoMarkovAnalysisProcess.h"
#include "ViewGoMarkov.h"
#include "GoMarkovOperatorFactory.h"
#include "GoMarkovOperator21.h"
#include "DialogGoMarkovCut.h"
using namespace std;

SceneGoMarkov::SceneGoMarkov(QObject *parent) : SceneGo(parent)
{
    this->_analysisTotalTime = 10.0;
    this->_analysisCount = 101;
    this->_analysisCutOrder = 1;
    this->selectTool(DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND);
}

void SceneGoMarkov::save(QDomDocument &document, QDomElement &root)
{
    QDomElement element = document.createElement("scene");
    element.setAttribute("analysis_total_time", this->_analysisTotalTime);
    element.setAttribute("analysis_count", this->_analysisCount);
    element.setAttribute("analysis_cut_order", this->_analysisCutOrder);
    QList<QGraphicsItem*> items = this->items();
    root.appendChild(element);
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        item->save(document, element);
    }
}

bool SceneGoMarkov::tryOpen(QDomElement &root)
{
    if (root.tagName() != "scene")
    {
        return false;
    }
    this->_analysisTotalTime = root.attribute("analysis_total_time", "10.0").toDouble();
    this->_analysisCount = root.attribute("analysis_count", "101").toDouble();
    this->_analysisCutOrder = root.attribute("analysis_cut_order", "2").toInt();
    bool flag = true;
    QList<ItemGoMarkovOperator*> operatorList;
    QList<ItemGoSignal*> signalList;
    QList<ItemGoMarkovEquivalent*> equivalentList;
    QList<ItemGoMarkovCommonCause*> commoncauseList;
    for (auto element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "operator")
        {
            ItemGoMarkovOperator *item = new ItemGoMarkovOperator();
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
        else if (element.tagName() == "equivalent")
        {
            ItemGoMarkovEquivalent *item = new ItemGoMarkovEquivalent();
            this->addItem(item);
            if (item->tryOpen(element))
            {
                equivalentList.push_back(item);
            }
            else
            {
                flag = false;
                this->removeItem(item);
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
        else if (element.tagName() == "commoncause")
        {
            ItemGoMarkovCommonCause *item = new ItemGoMarkovCommonCause();
            this->addItem(item);
            if (item->tryOpen(element))
            {
                commoncauseList.push_back(item);
            }
            else
            {
                flag = false;
                this->removeItem(item);
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
            if (signalList[i]->start()->op != nullptr && signalList[i]->end()->op != nullptr)
            {
                break;
            }
        }
        signalList[i]->updatePosition();
    }
    equivalentList = this->getTopologyOrder(equivalentList);
    for (int i = 0; i < equivalentList.size(); ++i)
    {
        equivalentList[i]->bindOperators(operatorList, equivalentList);
    }
    for (int i = 0; i < commoncauseList.size(); ++i)
    {
        commoncauseList[i]->bindOperators(operatorList);
    }
    operatorList.clear();
    signalList.clear();
    equivalentList.clear();
    commoncauseList.clear();
    return flag;
}

QSharedPointer<GoMarkovGraph> SceneGoMarkov::generateGoMarkovGraph()
{
    QSharedPointer<GoMarkovGraph> graph(new GoMarkovGraph());
    QList<QGraphicsItem*> items = this->items();
    QVector<ItemGoMarkovOperator*> operators;
    QVector<ItemGoMarkovOperator*> equivalentOperators;
    QVector<GoSignal*> generateSignals;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGoMarkovEquivalent *eq = (ItemGoMarkovEquivalent*)item;
            if (eq->fatherEquivalent() == nullptr)
            {
                equivalentOperators.push_back(eq->getEquivalentOperatorItem());
                operators.push_back(equivalentOperators.at(equivalentOperators.size() - 1));
                graph->addOperator(equivalentOperators.at(equivalentOperators.size() - 1)->model());
            }
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
        {
            ItemGoMarkovCommonCause *common = (ItemGoMarkovCommonCause*)item;
            graph->addCommonCause(common->model());
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            if (op->fatherEquivalent() == nullptr)
            {
                graph->addOperator(((ItemGoMarkovOperator*)item)->model());
            }
            operators.push_back((ItemGoMarkovOperator*)item);
        }
    }
    for (int i = 0; i < operators.size(); ++i)
    {
        ItemGoMarkovOperator *op = operators[i];
        op->model()->input()->clear();
        op->model()->subInput()->clear();
        for (int j = 0; j < op->model()->output()->number(); ++j)
        {
            op->model()->output()->signal()->at(j)->clear();
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal *itemSignal = (ItemGoSignal*)item;
            int u = itemSignal->start()->op->model()->realID();
            int v = itemSignal->end()->op->model()->realID();
            bool insideU = false;
            bool insideV = false;
            GoMarkovOperator *operatorU = nullptr;
            GoMarkovOperator *operatorV = nullptr;
            for (int j = 0; j < operators.size(); ++j)
            {
                if (operators[j]->model()->realID() == u)
                {
                    if (operators[j]->fatherEquivalent() != nullptr)
                    {
                        insideU = true;
                        u = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->realID() == u)
                            {
                                operatorU = (GoMarkovOperator*)operators[k]->model();
                                break;
                            }
                        }
                    }
                    else
                    {
                        operatorU = (GoMarkovOperator*)operators[j]->model();
                    }
                }
                if (operators[j]->model()->realID() == v)
                {
                    if (operators[j]->fatherEquivalent() != nullptr)
                    {
                        insideV = true;
                        v = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->realID() == v)
                            {
                                operatorV = (GoMarkovOperator*)operators[k]->model();
                                break;
                            }
                        }
                    }
                    else
                    {
                        operatorV = (GoMarkovOperator*)operators[j]->model();
                    }
                }
            }
            if (insideU && insideV)
            {
                continue;
            }
            if (operatorU == nullptr || operatorV == nullptr)
            {
                continue;
            }
            if (!insideU && !insideV)
            {
                itemSignal->model()->setU(operatorU);
                itemSignal->model()->setV(operatorV);
                operatorU->output()->addSignal(itemSignal->start()->index, itemSignal->model());
                if (itemSignal->end()->type == DefinationGoType::GO_OPERATOR_INPUT)
                {
                    operatorV->input()->set(itemSignal->end()->index, itemSignal->model());
                }
                else
                {
                    operatorV->subInput()->set(itemSignal->end()->index, itemSignal->model());
                }
            }
            else
            {
                GoSignal *signal = new GoSignal;
                generateSignals.push_back(signal);
                signal->setU(operatorU);
                signal->setV(operatorV);
                operatorU->output()->addSignal(itemSignal->start()->index, signal);
                if (itemSignal->end()->type == DefinationGoType::GO_OPERATOR_INPUT)
                {
                    operatorV->input()->set(itemSignal->end()->index, signal);
                }
                else
                {
                    operatorV->subInput()->set(itemSignal->end()->index, signal);
                }
            }
        }
    }
    return graph;
}

QSharedPointer<GoMarkovGraph> SceneGoMarkov::generateGoMarkovSimpleGraph()
{
    QSharedPointer<GoMarkovGraph> graph(new GoMarkovGraph());
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            op->model()->input()->clear();
            op->model()->subInput()->clear();
            for (int j = 0; j < op->model()->output()->number(); ++j)
            {
                op->model()->output()->signal()->at(j)->clear();
            }
        }
    }
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* opItem = (ItemGoMarkovOperator*)item;
            GoMarkovOperator* op = (GoMarkovOperator*)opItem->model();
            if (!op->isGlobalFeedback() || op->type() == GoMarkovOperatorFactory::Operator_Type_21)
            {
                graph->addOperator(op);
            }
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            ItemGoSignal* siItem = (ItemGoSignal*)item;
            GoSignal* signal = siItem->model();
            ItemGoMarkovOperator* uOpItem = (ItemGoMarkovOperator*)siItem->start()->op;
            ItemGoMarkovOperator* vOpItem = (ItemGoMarkovOperator*)siItem->end()->op;
            int uIndex = siItem->start()->index;
            int vIndex = siItem->end()->index;
            int vType = siItem->end()->type;
            uOpItem->model()->output()->addSignal(uIndex, signal);
            if (vType == DefinationGoType::GO_OPERATOR_INPUT)
            {
                vOpItem->model()->input()->set(vIndex, signal);
            }
            else
            {
                vOpItem->model()->subInput()->set(vIndex, signal);
            }
            signal->setU(uOpItem->model());
            signal->setV(vOpItem->model());
        }
    }
    return graph;
}

QSharedPointer<GoMarkovGraph> SceneGoMarkov::generateGoMarkovSimpleSubGraph(ItemGoMarkovOperator *last)
{
    QSharedPointer<GoMarkovGraph> graph(new GoMarkovGraph());
    QList<QGraphicsItem*> items = this->items();
    QVector<ItemGoSignal*> signalItems;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
        {
            signalItems.push_back((ItemGoSignal*)item);
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
            op->model()->input()->clear();
            op->model()->subInput()->clear();
            for (int j = 0; j < op->model()->output()->number(); ++j)
            {
                op->model()->output()->signal()->at(j)->clear();
            }
        }
    }
    QVector<ItemGoMarkovOperator*> operators;
    operators.push_back(last);
    for (int i = 0; i < operators.size(); ++i)
    {
        if (i)
        {
            graph->addOperator(operators[i]->model());
        }
        for (int j = 0; j < signalItems.size(); ++j)
        {
            if (signalItems[j]->end()->op == operators[i])
            {
                ItemGoSignal* siItem = signalItems[j];
                GoSignal* signal = siItem->model();
                ItemGoMarkovOperator* uOpItem = (ItemGoMarkovOperator*)siItem->start()->op;
                ItemGoMarkovOperator* vOpItem = (ItemGoMarkovOperator*)siItem->end()->op;
                if (i)
                {
                    int uIndex = siItem->start()->index;
                    int vIndex = siItem->end()->index;
                    int vType = siItem->end()->type;
                    uOpItem->model()->output()->addSignal(uIndex, signal);
                    if (vType == DefinationGoType::GO_OPERATOR_INPUT)
                    {
                        vOpItem->model()->input()->set(vIndex, signal);
                    }
                    else
                    {
                        vOpItem->model()->subInput()->set(vIndex, signal);
                    }
                    signal->setU(uOpItem->model());
                    signal->setV(vOpItem->model());
                }
                bool flag = true;
                for (int k = 0; k < operators.size(); ++k)
                {
                    if (operators[k] == uOpItem)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    operators.push_back(uOpItem);
                }
            }
        }
    }
    return graph;
}

void SceneGoMarkov::initGlobalFeedbackCut(double interval, int count)
{
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* opItem = (ItemGoMarkovOperator*)item;
            if (opItem->model()->type() == GoMarkovOperatorFactory::Operator_Type_21)
            {
                QSharedPointer<GoMarkovGraph> graph = this->generateGoMarkovSimpleSubGraph(opItem);
                GoPathSetSetSet cut = graph->findCut(graph->getOperator().size());
                cut.setIsCut(true);
                cut.setInterval(interval);
                cut.setCount(count);
                cut.calcWithTime();
                GoMarkovOperator21* op21 = (GoMarkovOperator21*)opItem->model();\
                op21->setCutProbability(cut.totalMarkovProbability(0));
                op21->savedProbabilites().clear();
                for (int i = 0; i < count; ++i)
                {
                    op21->savedProbabilites().push_back(cut.totalMarkovProbability(0, i));
                }
            }
        }
    }
}

void SceneGoMarkov::initGlobalFeedbackPath(double interval, int count)
{
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGoMarkovOperator* opItem = (ItemGoMarkovOperator*)item;
            if (opItem->model()->type() == GoMarkovOperatorFactory::Operator_Type_21)
            {
                QSharedPointer<GoMarkovGraph> graph = this->generateGoMarkovSimpleSubGraph(opItem);
                GoPathSetSetSet path = graph->findPath(graph->getOperator().size());
                path.setIsCut(false);
                path.setInterval(interval);
                path.setCount(count);
                path.calcWithTime();
                GoMarkovOperator21* op21 = (GoMarkovOperator21*)opItem->model();
                op21->setCutProbability(path.totalMarkovProbability(0));
                op21->savedProbabilites().clear();
                for (int i = 0; i < count; ++i)
                {
                    op21->savedProbabilites().push_back(path.totalMarkovProbability(0, i));
                }
            }
        }
    }
}

QList<ItemGoMarkovEquivalent*> SceneGoMarkov::getTopologyOrder(QList<ItemGoMarkovEquivalent*> equivalents)
{
    for (int i = 0; i < equivalents.size(); ++i)
    {
        for (int j = 0; j < equivalents[i]->model()->idList()->size(); ++j)
        {
            for (int k = 0; k < equivalents.size(); ++k)
            {
                if (equivalents[i]->model()->idList()->at(j) == equivalents[k]->id())
                {
                    equivalents[k]->setFatherEquivalent(equivalents[i]);
                    break;
                }
            }
        }
    }
    QVector<int> inputNumber;
    for (int i = 0; i < equivalents.size(); ++i)
    {
        inputNumber.push_back(0);
    }
    for (int i = 0; i < equivalents.size(); ++i)
    {
        ItemGoMarkovEquivalent *equivalent = equivalents[i]->fatherEquivalent();
        if (equivalent != nullptr)
        {
            for (int j = 0; j < equivalents.size(); ++j)
            {
                if (equivalents[j] == equivalent)
                {
                    ++inputNumber[j];
                }
            }
        }
    }
    QList<ItemGoMarkovEquivalent*> order;
    for (int i = 0; i < equivalents.size(); ++i)
    {
        if (inputNumber[i] == 0)
        {
            order.push_back(equivalents[i]);
        }
    }
    for (int i = 0; i < order.size(); ++i)
    {
        ItemGoMarkovEquivalent *equivalent = order[i]->fatherEquivalent();
        if (equivalent != nullptr)
        {
            for (int j = 0; j < equivalents.size(); ++j)
            {
                if (equivalents[j] == equivalent)
                {
                    if (--inputNumber[j] == 0)
                    {
                        order.push_back(equivalents[j]);
                    }
                }
            }
        }
    }
    return order;
}

void SceneGoMarkov::analysisProbability(const QString filePath)
{
    DialogGoMarkovPeriod dialog;
    dialog.setTotalTime(this->_analysisTotalTime);
    dialog.setCount(this->_analysisCount);
    if (QDialog::Accepted == dialog.exec())
    {
        QSharedPointer<GoMarkovGraph> graph = this->generateGoMarkovGraph();
        double totalTime = dialog.totalTime();
        int count = dialog.count();
        this->_analysisTotalTime = totalTime;
        this->_analysisCount = count;

        DialogGoMarkovAnalysisProcess processDialog;
        processDialog.setMarkovGraph(graph);
        processDialog.setTotalTime(totalTime);
        processDialog.setTotalCount(count);
        if (QDialog::Accepted == processDialog.exec())
        {
            QSharedPointer<GoMarkovChartData> data = processDialog.analysisResult();
            QVector<GoGraph::MessageRecord> messages = graph->messages();
            for (int i = 0; i < messages.size(); ++i)
            {
                QSharedPointer<Message> message = MessageFactory::produce(messages[i].type);
                message->paramString = messages[i].message;
                this->send(message);
            }
            if (!data.isNull())
            {
                if (data->saveAsHTML(filePath + ".goc.html"))
                {
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
                    message->paramString = filePath + ".goc.html";
                    this->send(message);
                }
            }
        }
    }
}

void SceneGoMarkov::analysisCut(const QString filePath)
{
    DialogGoMarkovCut dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        this->initGlobalFeedbackCut(dialog.interval(), dialog.count());
        QSharedPointer<GoMarkovGraph> graph = this->generateGoMarkovSimpleGraph();
        this->_analysisCutOrder = dialog.order();
        GoPathSetSetSet cut = graph->findCut(dialog.order());
        cut.setIsCut(true);
        cut.setInterval(dialog.interval());
        cut.setCount(dialog.count());
        cut.calcWithTime();
        if (graph->getErrorMessage() == "")
        {
            graph->saveAsHTML(filePath + ".cut.html", cut);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
            message->paramString = filePath + ".cut.html";
            this->send(message);
        }
        else
        {
            QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
        }
    }
}

void SceneGoMarkov::analysisPath(const QString filePath)
{
    DialogGoMarkovCut dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        this->initGlobalFeedbackPath(dialog.interval(), dialog.count());
        QSharedPointer<GoMarkovGraph> graph = this->generateGoMarkovSimpleGraph();
        this->_analysisCutOrder = dialog.order();
        GoPathSetSetSet path = graph->findPath(dialog.order());
        path.setIsCut(false);
        path.setInterval(dialog.interval());
        path.setCount(dialog.count());
        path.calcWithTime();
        if (graph->getErrorMessage() == "")
        {
            graph->saveAsHTML(filePath + ".path.html", path);
            QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
            message->paramString = filePath + ".path.html";
            this->send(message);
        }
        else
        {
            QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
        }
    }
}
