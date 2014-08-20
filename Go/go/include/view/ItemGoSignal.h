#ifndef ITEMGOSIGNAL_H
#define ITEMGOSIGNAL_H
#include "ItemDrawable.h"
#include "DomItem.h"
#include "IdentifiedItem.h"
#include "GoSignal.h"

class ItemGoOperator;

class ItemGoSignal : public ItemDrawable, public IdentifiedItem
{
public:
    struct SignalConnection
    {
        ItemGoOperator *op;
        int id; /** 只应用于初始化操作。 */
        int type;
        int index;
    };

    ItemGoSignal(QGraphicsItem *parent = 0);
    ~ItemGoSignal();
    QRectF boundingRect() const;
    bool isSelectable(float x, float y);
    bool isSelectable(float x, float y, float width, float height);
    bool isCornerLineSelectable(float x, float y);
    SignalConnection* start();
    SignalConnection* end();
    QPointF endPos() const;
    void setEndPosition(QPointF pos);
    void setEndPosition(int x, int y);
    bool isStraightLine() const;
    bool isBrokenLine() const;
    void setIsStraightLine(const bool value);
    void setIsBrokenLine(const bool value);
    float cornerProportion() const;
    void setCornerProportion(const float value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    void updatePosition();
    void removeConnection();
    ItemGoSignal* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    GoSignal *model() const;

protected:
    SignalConnection *_start;
    SignalConnection *_end;
    QPointF _endPos;
    bool _isStraightLine;
    float _cornerProportion;
    GoSignal *_model;
};

#endif // ITEMGOSIGNAL_H
