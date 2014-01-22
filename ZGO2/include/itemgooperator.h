#ifndef ITEMGOOPERATOR_H
#define ITEMGOOPERATOR_H
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
    virtual void setModel(GOOperator *model);
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
    QVector<ItemGOSignal*>* input() const;
    QVector<ItemGOSignal*>* subInput() const;
    QVector<QVector<ItemGOSignal*>*>* output() const;
    void setSignal(ItemGOSignal *signal, int type, int index);
    void removeSignal(ItemGOSignal *signal, int type, int index);
    QList<ItemGOSignal*> getConnectedSignals() const;
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
    QVector<ItemGOSignal*> *_inputSignal;
    QVector<ItemGOSignal*> *_subInputSignal;
    QVector<QVector<ItemGOSignal*>*> *_outputSignal;
    QVector<bool> *_isShowOutput;

    GOOperator *_model; /** The model of GO operator. */

    bool _isHorizonFlip;
    bool _isVerticalFlip;
    bool _isDrawParameter;
    bool _isDrawName;

    virtual bool isSource() const;
};

#endif // ITEMGOOPERATOR_H
