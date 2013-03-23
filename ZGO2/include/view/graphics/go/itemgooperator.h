#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
/**
 * The basic moveable GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "itemmoveable.h"

class ItemArrow;
class GOOperator;
class GOOperatorFactory;
class ItemGOSignal;

class ItemGOOperator : public ItemMoveable
{
public:
    ItemGOOperator(QGraphicsItem *parent = 0);
    virtual ~ItemGOOperator();
    GOOperator *model() const;
    void setModel(GOOperator *model);
    void updateGraphic();
    QRectF boundingRect() const;
    bool isSelected(float x, float y);
    bool isSelected(float x, float y, float width, float height);
    void move(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QPoint getInputPosition(int index);
    QPoint getSubInputPosition(int index = 0);
    QPoint getOutputPosition(int index);
    void setSignal(ItemGOSignal *signal, int type, int index);
    void removeSignal(ItemGOSignal *signal, int type, int index);
    QList<ItemGOSignal*> getConnectedSignals() const;

protected:
    QVector<ItemArrow*> *_inputArrows; /** Main input arrows. */
    QVector<ItemArrow*> *_subInputArrows; /** Sub input arrows.  */
    QVector<ItemArrow*> *_outputArrows; /** Output arrows. */
    QVector<ItemGOSignal*> *_inputSignal;
    QVector<ItemGOSignal*> *_subInputSignal;
    QVector<QVector<ItemGOSignal*>*> *_outputSignal;

    GOOperator *_model; /** The model of GO operator. */
};

#endif // ITEMGOOPERATOR_H
