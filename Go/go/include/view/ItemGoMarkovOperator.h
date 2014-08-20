#ifndef ITEMGOMARKOVOPERATOR_H
#define ITEMGOMARKOVOPERATOR_H
#include "ItemGoOperator.h"

class ItemGoMarkovEquivalent;
class ItemGoMarkovCommonCause;

class ItemGoMarkovOperator : public ItemGoOperator
{
public:
    ItemGoMarkovOperator(QGraphicsItem *parent = 0);
    ItemGoMarkovEquivalent* fatherEquivalent() const;
    ItemGoMarkovEquivalent* rootEquivalent() const;
    void setFatherEquivalent(ItemGoMarkovEquivalent* equivalent);
    ItemGoMarkovCommonCause* fatherCommonCause() const;
    void setFatherCommonCause(ItemGoMarkovCommonCause* commonCause);
    void move(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void setModelType(const int type);
    void setModel(GoOperator *model);
    void globalFeedbackExtend();
    QRectF boundingRect() const;
    ItemGoMarkovOperator* copy();
    bool tryOpen(QDomElement &root);

protected:
    ItemGoMarkovEquivalent *_fatherEquivalent;
    ItemGoMarkovCommonCause *_fatherCommonCause;
    bool isSource() const;
    void paint(QPainter *painter);
    void paint9A(QPainter *painter);
    void paint22B(QPainter *painter);
    void paintSplit(QPainter *painter);
    void updateArrowColor();
};

#endif // ITEMGOMARKOVOPERATOR_H
