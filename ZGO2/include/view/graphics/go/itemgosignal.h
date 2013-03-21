#ifndef ITEMGOSIGNAL_H
#define ITEMGOSIGNAL_H
/**
 * The signal of the GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemdrawable.h"

class ItemGOOperator;

class ItemGOSignal : public ItemDrawable
{
public:
    struct SignalConnection
    {
        ItemGOOperator *op;
        int type;
        int index;
    };

    ItemGOSignal(QGraphicsItem *parent = 0);
    ~ItemGOSignal();
    SignalConnection* start();
    SignalConnection* end();
    void setEndPosition(QPointF pos);
    void setEndPosition(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void updatePosition();

protected:
    SignalConnection *_start;
    SignalConnection *_end;
    QPoint _endPos;
};

#endif // ITEMGOSIGNAL_H
