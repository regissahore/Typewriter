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

SceneGOMarkov::SceneGOMarkov(QObject *parent) : SceneGO(parent)
{
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
    for (int i = 0; i < equivalentList.size(); ++i)
    {
        equivalentList[i]->bindOperators(operatorList, equivalentList);
    }
    operatorList.clear();
    signalList.clear();
    equivalentList.clear();
    return flag;
}

GOGraph* SceneGOMarkov::generatorGOGraph()
{
    GOGraph *graph = new GOMarkovGraph();
    QList<QGraphicsItem*> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)items[i];
        switch (item->TypedItem::type())
        {
        case DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR:
            graph->addOperator(((ItemGOMarkovOperator*)item)->model());
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
