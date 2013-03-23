#include <QtAlgorithms>
#include "toolgoselect.h"
#include "itemgooperator.h"
#include "itemgosignal.h"
#include "definationeditorselectiontype.h"

/**
 * Constructor.
 * @param sceneGO The SceneGO entity.
 */
ToolGOSelect::ToolGOSelect(SceneGO *sceneGO) : ToolGOAbstract(sceneGO)
{
    this->graphicsView()->setDragMode(QGraphicsView::NoDrag);
    this->_selection = new ItemSelection();
    this->graphicsScene()->addItem(this->_selection);
    this->_status = Status_Null;
}

/**
 * Clear.
 */
ToolGOSelect::~ToolGOSelect()
{
    this->_items.clear();
    this->graphicsScene()->removeItem(this->_selection);
    delete this->_selection;
}

/**
 * Mouse press event.
 * @param event Mouse event.
 */
void ToolGOSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Null:
        this->_status = Status_Selecting;
        this->_selection->setPos(QPoint(event->scenePos().x(), event->scenePos().y()));
        this->_selection->setEnd(QPoint(0, 0));
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(), event->scenePos().y()))
        {
            this->_status = Status_Moving;
            for (int i = 0; i < this->_items.size(); ++i)
            {
                ((ItemMoveable*)this->_items[i])->ItemMoveable::startMove(event);
            }
            this->_selection->startMove(event);
        }
        else
        {
            this->_status = Status_Selecting;
            this->_selection->setPos(QPoint(event->scenePos().x(), event->scenePos().y()));
            this->_selection->setEnd(QPoint(0, 0));
        }
        break;
    default:
        break;
    }
}

/**
 * Mouse move event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Selecting:
        this->_selection->setEnd(QPoint(event->scenePos().x() - this->_selection->pos().x(),
                                        event->scenePos().y() - this->_selection->pos().y()));
        this->_selection->update();
        break;
    case Status_Selected:
        if (this->_selection->isInside(event->scenePos().x(), event->scenePos().y()))
        {
            this->graphicsView()->setCursor(Qt::SizeAllCursor);
        }
        else
        {
            this->graphicsView()->setCursor(Qt::ArrowCursor);
        }
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            ((ItemMoveable*)this->_items[i])->ItemMoveable::move(event);
        }
        this->_selection->move(event);
        break;
    default:
        break;
    }
}

/**
 * Mouse release event.
 * @param event Mouse event.
 */
void ToolGOSelect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->_status)
    {
    case Status_Selecting:
        this->_status = Status_Selected;
        this->_items = this->graphicsScene()->items(this->_selection->pos().x(),
                                                    this->_selection->pos().y(),
                                                    this->_selection->end().x(),
                                                    this->_selection->end().y());
        break;
    case Status_Moving:
        for (int i = 0; i < this->_items.size(); ++i)
        {
            ((ItemMoveable*)this->_items[i])->ItemMoveable::stopMove(event);
        }
        this->_selection->stopMove(event);
        this->_status = Status_Selected;
        break;
    default:
        break;
    }
}

/**
 * Key Release event.
 * @param event Key event.
 */
void ToolGOSelect::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QVector<ItemGOSignal*> allSignal;
        QVector<ItemGOSignal*> selectedSignal;
        for (int i = 0; i < this->_items.size(); ++i)
        {
            int type = ((ItemDrawable*)this->_items[i])->TypedItem::type();
            if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
            {
                QList<ItemGOSignal*> signal = ((ItemGOOperator*)this->_items[i])->getConnectedSignals();
                for (int j = 0; j < signal.size(); ++j)
                {
                    allSignal.push_back(signal[j]);
                }
            }
            else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
            {
                selectedSignal.push_back((ItemGOSignal*)this->_items[i]);
            }
        }
        for (int i = allSignal.size() - 1; i >= 0; --i)
        {
            for (int j = 0; j < selectedSignal.size(); ++j)
            {
                if (allSignal[i] == selectedSignal[j])
                {
                    allSignal.remove(i);
                    break;
                }
            }
        }
        qSort(allSignal.begin(), allSignal.end());
        for (int i = 0; i < allSignal.size(); ++i)
        {
            if (i == 0)
            {
                allSignal[i]->removeConnection();
                delete allSignal[i];
            }
            else
            {
                if (allSignal[i] != allSignal[i - 1])
                {
                    allSignal[i]->removeConnection();
                    delete allSignal[i];
                }
            }
        }
        for (int i = 0; i < this->_items.size(); ++i)
        {
            int type = ((ItemDrawable*)this->_items[i])->TypedItem::type();
            if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_OPERATOR)
            {
                delete (ItemGOOperator*)this->_items[i];
            }
            else if (type == DefinationEditorSelectionType::EDITOR_SELECTION_GO_SIGNAL)
            {
                delete (ItemGOSignal*)this->_items[i];
            }
            else
            {
                delete (ItemDrawable*)this->_items[i];
            }
        }
        allSignal.clear();
    }
}
