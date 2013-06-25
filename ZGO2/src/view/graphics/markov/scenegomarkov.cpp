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
#include "gomarkovcommoncause.h"

SceneGOMarkov::SceneGOMarkov(QObject *parent) : SceneGO(parent)
{
    this->selectTool(DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND);
}

bool SceneGOMarkov::tryOpen(QDomElement &root)
{
    if (root.tagName() != "scene")
    {
        return false;
    }
    bool flag = true;
    QList<ItemGOMarkovOperator*> operatorList;
    QList<ItemGOSignal*> signalList;
    QList<ItemGOMarkovEquivalent*> equivalentList;
    QList<ItemGOMarkovCommonCause*> commoncauseList;
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
            ItemGOMarkovCommonCause *item = new ItemGOMarkovCommonCause();
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
            int u = itemSignal->start()->op->model()->id();
            int v = itemSignal->end()->op->model()->id();
            bool insideU = false;
            bool insideV = false;
            GOMarkovOperator *operatorU = 0L;
            GOMarkovOperator *operatorV = 0L;
            for (int j = 0; j < operators.size(); ++j)
            {
                if (operators[j]->model()->id() == u)
                {
                    if (operators[j]->fatherEquivalent() != 0L)
                    {
                        insideU = true;
                        u = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->id() == u)
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
                if (operators[j]->model()->id() == v)
                {
                    if (operators[j]->fatherEquivalent() != 0L)
                    {
                        insideV = true;
                        v = operators[j]->rootEquivalent()->id();
                        for (int k = 0; k < operators.size(); ++k)
                        {
                            if (operators[k]->model()->id() == v)
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
    if (QDialog::Accepted == dialog->exec())
    {
        GOMarkovGraph *graph = (GOMarkovGraph*)this->generatorGOGraph();
        double totalTime = dialog->totalTime();
        int count = dialog->count();
        GOMarkovChartData *data = graph->calcAccumulativeProbability(totalTime, count);
        if (data != 0L)
        {
            if (data->save(filePath + ".goc"))
            {
                Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
                message->paramString = filePath + ".goc";
                this->sendMessage(message);
            }
            if (data->saveAsHTML(filePath + ".goc.html"))
            {
                Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_OPEN_EXIST);
                message->paramString = filePath + ".goc.html";
                this->sendMessage(message);
            }
            delete data;
        }
        else
        {
            QMessageBox::information(0, tr("Error"), graph->getErrorMessage());
        }
    }
}
