#include "toolgomarkovcommoncause.h"
#include "scenego.h"
#include "messagefactory.h"
#include "definationtooltype.h"
#include "definationeditorselectiontype.h"
#include "itemdrawable.h"
#include "itemgomarkovoperator.h"
#include "itemgomarkovcommoncause.h"
#include "gomarkovcommoncause.h"
#include "gomarkovoperator.h"

ToolGOMarkovCommonCause::ToolGOMarkovCommonCause(SceneGO *sceneGO) : ToolGOSelect(sceneGO)
{
}

void ToolGOMarkovCommonCause::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *> items;
        float x, y, width, height;
        switch (this->_status)
        {
        case Status_Selecting:
            if (this->_selection->end().x() >= 0)
            {
                x = this->_selection->pos().x();
                width = this->_selection->end().x();
            }
            else
            {
                x = this->_selection->pos().x() + this->_selection->end().x();
                width = -this->_selection->end().x();
            }
            if (this->_selection->end().y() >= 0)
            {
                y = this->_selection->pos().y();
                height = this->_selection->end().y();
            }
            else
            {
                y = this->_selection->pos().y() + this->_selection->end().y();
                height = -this->_selection->end().y();
            }
            items = this->graphicsScene()->items(QRectF(x, y, width, height),
                                                 Qt::IntersectsItemBoundingRect);
            this->_items.clear();
            for (int i = 0; i < items.size(); ++i)
            {
                if (items[i] == this->_selection)
                {
                    continue;
                }
                if (((ItemDrawable*)items[i])->isSelectable(this->_selection->pos().x(),
                                                          this->_selection->pos().y(),
                                                          this->_selection->end().x(),
                                                          this->_selection->end().y()))
                {
                    this->_items.push_back(items[i]);
                }
            }
            this->addCommonCause();
            this->_selection->setVisible(false);
            this->_selection->update();
            this->_status = Status_Null;
            break;
        default:
            break;
        }
        items.clear();
    }
    else
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOMarkovCommonCause::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        Message *message = MessageFactory::produce(MessageFactory::TYPE_TOOL_SELECTION);
        message->paramInt = DefinationToolType::TOOL_TYPE_GO_MARKOV_POINTER_EXTEND;
        this->sceneGO()->sendMessage(message);
    }
}

void ToolGOMarkovCommonCause::addCommonCause()
{
    bool flag = true;
    QVector<ItemGOMarkovOperator*> operators;
    for (qint32 i = 0; i < this->_items.size(); ++i)
    {
        ItemDrawable *item = (ItemDrawable*)this->_items.at(i);
        if (item->TypedItem::type() == DefinationEditorSelectionType::EDITOR_SELECTION_GO_MARKOV_OPERATOR)
        {
            ItemGOMarkovOperator* markov = (ItemGOMarkovOperator*)item;
            if (markov->fatherCommonCause() || markov->fatherEquivalent())
            {
                flag = false;
                break;
            }
            operators.push_back(markov);
        }
    }
    if (operators.size() < 2)
    {
        flag = false;
    }
    if (flag)
    {
        ItemGOMarkovCommonCause *common = new ItemGOMarkovCommonCause();
        for (int i = 0; i < operators.size(); ++i)
        {
            common->operatorItems()->push_back(operators[i]);
            common->model()->operators()->push_back((GOMarkovOperator*)(operators[i]->model()));
            common->model()->idList()->push_back(((GOMarkovOperator*)(operators[i]->model()))->id());
            operators[i]->setFatherCommonCause(common);
        }
        common->updateBoundary();
        this->graphicsScene()->addItem(common);
        Message *message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
        message->setMessage(common);
        this->sceneGO()->sendMessage(message);
    }
}
