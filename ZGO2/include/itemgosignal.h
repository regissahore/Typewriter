#ifndef ITEMGOSIGNAL_H
#define ITEMGOSIGNAL_H
/**
 * The signal of the GO graph.
 * The signal should be deleted before the deleting operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "itemdrawable.h"
#include "domitem.h"
#include "identifieditem.h"
#include "gosignal.h"

class ItemGOOperator;

class ItemGOSignal : public ItemDrawable, public IdentifiedItem
{
public:
    struct SignalConnection
    {
        ItemGOOperator *op;
        int id; /** Just use for initialization. */
        int type;
        int index;
    };

    ItemGOSignal(QGraphicsItem *parent = 0);
    ~ItemGOSignal();
    QRectF boundingRect() const;
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float width, float height);
    SignalConnection* start();
    SignalConnection* end();
    void setEndPosition(QPointF pos);
    void setEndPosition(int x, int y);
    double cornerX() const;
    void setCornerX(const double value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void updatePosition();
    void removeConnection();
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    GOSignal *model();

protected:
    SignalConnection *_start;
    SignalConnection *_end;
    QPoint _endPos;
    double _cornerX;
    GOSignal *_model;
};

#endif // ITEMGOSIGNAL_H
