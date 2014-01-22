#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
#include <QVector>
#include "ItemMoveable.h"

class ItemArrow;
class GoOperator;
class GoOperatorFactory;
class ItemGoSignal;

class ItemGoOperator : public ItemMoveable
{
public:
    ItemGoOperator(QGraphicsItem *parent = 0);
    virtual ~ItemGoOperator();
    virtual void setModelType(const int type);
    GoOperator *model() const;
    virtual void setModel(GoOperator *model);
    QRectF boundingRect() const;
    void expandId(const int id);
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
    QPoint getInputDeepPosition(int index);
    QPoint getSubInputDeepPosition(int index = 0);
    QVector<ItemGoSignal*>* input() const;
    QVector<ItemGoSignal*>* subInput() const;
    QVector<QVector<ItemGoSignal*>*>* output() const;
    void setSignal(ItemGoSignal *signal, int type, int index);
    void removeSignal(ItemGoSignal *signal, int type, int index);
    QList<ItemGoSignal*> getConnectedSignals() const;
    QVector<bool>* isShowOutput() const;
    bool isDrawParameter() const;
    void setIsDrawParameter(const bool value);
    bool isDrawName() const;
    void setIsDrawName(const bool value);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    QVector<ItemArrow*> *_inputArrows; /** Main input arrows. */
    QVector<ItemArrow*> *_subInputArrows; /** Sub input arrows.  */
    QVector<ItemArrow*> *_outputArrows; /** Output arrows. */
    QVector<ItemGoSignal*> *_inputSignal;
    QVector<ItemGoSignal*> *_subInputSignal;
    QVector<QVector<ItemGoSignal*>*> *_outputSignal;
    QVector<bool> *_isShowOutput;

    GoOperator *_model; /** The model of Go operator. */

    bool _isHorizonFlip;
    bool _isVerticalFlip;
    bool _isDrawParameter;
    bool _isDrawName;

    virtual bool isSource() const;
};

#endif // ITEMGOOPERATOR_H
