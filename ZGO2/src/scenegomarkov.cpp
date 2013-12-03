#include <QMessageBox>
#include "scenegomarkov.h"
#include "itemgomarkovoperator.h"
#include "itemgosignal.h"
#include "itemgotext.h"
#include "gomarkovoperator.h"
#include "gomarkovgraph.h"
#include "definationeditorselectiontype.h"
#include "definationgotype.h"
#include "goinput.h"
#include "gooutput.h"
#include "itemgomarkovequivalent.h"
#include "definationtooltype.h"
#include "dialoggomarkovperiod.h"
#include "messagefactory.h"
#include "gomarkovchartdata.h"
#include "gomarkovequivalent.h"
#include "itemgomarkovcommoncause.h"
#include "itemgomarkovcommoncause2.h"
#include "gomarkovcommoncause.h"
#include "dialogintegerinput.h"
#include "gopathsetsetset.h"
#include "dialoggomarkovanalysisprocess.h"
#include "viewgomarkov.h"

SceneGOMarkov::SceneGOMarkov(QObject *parent) : SceneGO(parent)
{
    this->_analysisTotalTime = 10.0;
    this->_analysisCount = 101;
    this->_analysisCutOrder = 1;
    this->selectTool(DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND);
}

void SceneGOMarkov::save(QDomDocument &document, QDomElement &root)
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

bool SceneGOMarkov::tryOpen(QDomElement &root)
{
    if (root.tagName() != "scene")
    {
        return false;
    }
    this->_analysisTotalTime = root.attribute("analysis_total_time", "10.0").toDouble();
    this->_analysisCount = root.attribute("analysis_count", "101").toDouble();
    this->_analysisCutOrder = root.attribute("analysis_cut_order", "2").toInt();
    bool flag = true;
    QList<ItemGOMarkovOperator*> operatorList;
    QList<ItemGOSignal*> signalList;
    QList<ItemGOMarkovEquivalent*> equivalentList;
    QList<ItemGOMarkovCommonCause2*> commoncauseList;
    for (QDomElement element = root.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "operator")
        {
            ItemGOMarkovOperator *item = new ItemGOMarkovOperator();
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
        else if (element.tagName() == "equivalent")
        {
            ItemGOMarkovEquivalent *item = new ItemGOMarkovEquivalent();
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
            ItemGOText *item = new ItemGOText();
            if (item->tryOpen(element))
            {
                this->addItem(item);
            }
        }
        else if (element.tagName() == "commoncause")
        {
            ItemGOMarkovCommonCause2 *item = new ItemGOMarkovCommonCause2();
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
            if (signalList[i]->start()->op != 0L && signalList[i]->end()->op != 0L)
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

GOGraph* SceneGOMarkov::generatorGOGraph()
{
    GOMarkovGraph *graph = new GOMarkovGraph();
    graph->bindMessage(this->MessageListener::_messageController);
    QList<QGraphicsItem*> items = this->items();
    QVector<ItemGOMarkovOperator*> operators;
    QVector<ItemGOMarkovOperator*> equivalentOperators;
    QVector<GOSignal*> generateSignals;
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_EQUIVALENT)
        {
            ItemGOMarkovEquivalent *eq = (ItemGOMarkovEquivalent*)item;
            if (eq->fatherEquivalent() == 0L)
            {
                equivalentOperators.push_back(eq->getEquivalentOperatorItem());
                operators.push_back(equivalentOperators.at(equivalentOperators.size() - 1));
                graph->addOperator(equivalentOperators.at(equivalentOperators.size() - 1)->model());
            }
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE)
        {
            ItemGOMarkovCommonCause *common = (ItemGOMarkovCommonCause*)item;
            graph->addCommonCause(common->model());
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_COMMON_CAUSE_2)
        {
            ItemGOMarkovCommonCause2 *common = (ItemGOMarkovCommonCause2*)item;
            graph->addCommonCause(common->model());
        }
        else if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
            if (op->fatherEquivalent() == 0L)
            {
                graph->addOperator(((ItemGOMarkovOperator*)item)->model());
            }
            operators.push_back((ItemGOMarkovOperator*)item);
        }
    }
    for (int i = 0; i < operators.size(); ++i)
    {
        ItemGOMarkovOperator *op = operators[i];
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
            ItemGOSignal *itemSignal = (ItemGOSignal*)item;
            int u = itemSignal->start()->op->model()->realID();
            int v = itemSignal->end()->op->model()->realID();
            bool insideU = false;
            bool insideV = false;
            GOMarkovOperator *operatorU = 0L;
            GOMarkovOperator *operatorV = 0L;
            for (int j = 0; j < operators.size(); ++j)
            {
                if (operators[j]->model()->realID() == u)
                {
                    if (operators[j]->fatherEquivalent() != 0L)
                    {
                        insideU = true;
                        u = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->realID() == u)
                            {
                                operatorU = (GOMarkovOperator*)operators[k]->model();
                                break;
                            }
                        }
                    }
                    else
                    {
                        operatorU = (GOMarkovOperator*)operators[j]->model();
                    }
                }
                if (operators[j]->model()->realID() == v)
                {
                    if (operators[j]->fatherEquivalent() != 0L)
                    {
                        insideV = true;
                        v = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->realID() == v)
                            {
                                operatorV = (GOMarkovOperator*)operators[k]->model();
                                break;
                            }
                        }
                    }
                    else
                    {
                        operatorV = (GOMarkovOperator*)operators[j]->model();
                    }
                }
            }
            if (insideU && insideV)
            {
                continue;
            }
            if (operatorU == 0L || operatorV == 0L)
            {
                continue;
            }
            if (!insideU && !insideV)
            {
                itemSignal->model()->setU(operatorU);
                itemSignal->model()->setV(operatorV);
                operatorU->output()->addSignal(itemSignal->start()->index, itemSignal->model());
                if (itemSignal->end()->type == DefinationGOType::GO_OPERATOR_INPUT)
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
                GOSignal *signal = new GOSignal;
                generateSignals.push_back(signal);
                signal->setU(operatorU);
                signal->setV(operatorV);
                operatorU->output()->addSignal(itemSignal->start()->index, signal);
                if (itemSignal->end()->type == DefinationGOType::GO_OPERATOR_INPUT)
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

QList<ItemGOMarkovEquivalent*> SceneGOMarkov::getTopologyOrder(QList<ItemGOMarkovEquivalent*> equivalents)
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
        ItemGOMarkovEquivalent *equivalent = equivalents[i]->fatherEquivalent();
        if (equivalent != 0L)
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
    QList<ItemGOMarkovEquivalent*> order;
    for (int i = 0; i < equivalents.size(); ++i)
    {
        if (inputNumber[i] == 0)
        {
            order.push_back(equivalents[i]);
        }
    }
    for (int i = 0; i < order.size(); ++i)
    {
        ItemGOMarkovEquivalent *equivalent = order[i]->fatherEquivalent();
        if (equivalent != 0L)
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

void SceneGOMarkov::analysisProbability(const QString filePath)
{
    DialogGOMarkovPeriod *dialog = new DialogGOMarkovPeriod();
    dialog->setTotalTime(this->_analysisTotalTime);
    dialog->setCount(this->_analysisCount);
    if (QDialog::Accepted == dialog->exec())
    {
        GOMarkovGraph *graph = (GOMarkovGraph*)this->generatorGOGraph();
        double totalTime = dialog->totalTime();
        int count = dialog->count();
        this->_analysisTotalTime = totalTime;
        this->_analysisCount = count;

        DialogGOMarkovAnalysisProcess *processDialog = new DialogGOMarkovAnalysisProcess();
        processDialog->setMarkovGraph(graph);
        processDialog->setTotalTime(totalTime);
        processDialog->setTotalCount(count);
        if (QDialog::Accepted == processDialog->exec())
        {
            GOMarkovChartData *data = processDialog->analysisResult();
            QVector<GOGraph::MessageRecord> messages = graph->messages();
            for (int i = 0; i < messages.size(); ++i)
            {
                QSharedPointer<Message> message = MessageFactory::produce(messages[i].type);
                message->paramString = messages[i].message;
                this->sendMessage(message);
            }
            if (data != 0L)
            {
                if (data->save(filePath + ".goc"))
                {
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
                    message->paramString = filePath + ".goc";
                    this->sendMessage(message);
                }
                if (data->saveAsHTML(filePath + ".goc.html"))
                {
                    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
                    message->paramString = filePath + ".goc.html";
                    this->sendMessage(message);
                }
                delete data;
            }
        }
        //delete processDialog;
    }
    delete dialog;
}

void SceneGOMarkov::analysisCut(const QString filePath)
{
    DialogIntegerInput *dialog = new DialogIntegerInput();
    dialog->setWindowTitle(QObject::tr("Set order"));
    dialog->setText(QObject::tr("Input cut order: "));
    dialog->integerInput()->setMinimum(1);
    dialog->integerInput()->setValue(this->_analysisCutOrder);
    if (dialog->exec() == QDialog::Accepted)
    {
        GOGraph *graph = this->generatorGOGraph();
        this->_analysisCutOrder = dialog->integerInput()->value();
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
