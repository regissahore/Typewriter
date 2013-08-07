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
    virtual void setModelType(const int type);
    GOOperator *model() const;
    void setModel(GOOperator *model);
    QRectF boundingRect() const;
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float width, float height);
    bool isHorizonFlip() const;
    bool isVerticalFlip() const;
    void horizonFlip();
    void verticalFlip();
    void setIsHorizonFlip(bool value);
    void setIsVerticalFlip(bool value);
    void move(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    QPoint getInputPosition(int index);
    QPoint getSubInputPosition(int index = 0);
    QPoint getOutputPosition(int index);
    QVector<ItemGOSignal*>* input() const;
    QVector<ItemGOSignal*>* subInput() const;
    QVector<QVector<ItemGOSignal*>*>* output() const;
    void setSignal(ItemGOSignal *signal, int type, int index);
    void removeSignal(ItemGOSignal *signal, int type, int index);
    QList<ItemGOSignal*> getConnectedSignals() const;
    QVector<bool>* isShowOutput() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<ItemArrow*> *_inputArrows; /** Main input arrows. */
    QVector<ItemArrow*> *_subInputArrows; /** Sub input arrows.  */
    QVector<ItemArrow*> *_outputArrows; /** Output arrows. */
    QVector<ItemGOSignal*> *_inputSignal;
    QVector<ItemGOSignal*> *_subInputSignal;
    QVector<QVector<ItemGOSignal*>*> *_outputSignal;
    QVector<bool> *_isShowOutput;

    GOOperator *_model; /** The model of GO operator. */

    bool _isHorizonFlip;
    bool _isVerticalFlip;

    virtual bool isSource() const;
};

#endif // ITEMGOOPERATOR_H
