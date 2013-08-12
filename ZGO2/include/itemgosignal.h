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
        int id; /** 只应用于初始化操作。 */
        int type;
        int index;
    };

    ItemGOSignal(QGraphicsItem *parent = 0);
    ~ItemGOSignal();
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
    ItemGOSignal* copy() const;
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    GOSignal *model() const;

protected:
    SignalConnection *_start;
    SignalConnection *_end;
    QPointF _endPos;
    bool _isStraightLine;
    float _cornerProportion;
    GOSignal *_model;
};

#endif // ITEMGOSIGNAL_H
