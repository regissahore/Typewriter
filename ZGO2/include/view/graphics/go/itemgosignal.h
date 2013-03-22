#ifndef ITEMGOSIGNAL_H
#define ITEMGOSIGNAL_H
/**
 * The signal of the GO graph.
 * The signal should be deleted before the deleting operator.
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
    QPainterPath shape() const;
    SignalConnection* start();
    SignalConnection* end();
    void setEndPosition(QPointF pos);
    void setEndPosition(int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void updatePosition();
    void removeConnection();

protected:
    SignalConnection *_start;
    SignalConnection *_end;
    QPoint _endPos;
};

#endif // ITEMGOSIGNAL_H
