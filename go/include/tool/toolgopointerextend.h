#ifndef TOOLGOPOINTEREXTEND_H
#define TOOLGOPOINTEREXTEND_H
#include "ToolGoAbstract.h"

class ItemGoSignal;
class ItemDrawable;

class ToolGoPointerExtend : public ToolGoAbstract
{
public:
    ToolGoPointerExtend(SceneGo *sceneGo);
    ~ToolGoPointerExtend();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    enum Status
    {
        Status_Null,
        Status_Scene_Moving,
        Status_Item_Moving,
        Status_Signal_Connecting,
        Status_Signal_Adjusting
    };
    Status _status;
    ItemDrawable* _item;
    ItemGoSignal* _signal;

    bool isAround(QPointF pos1, QPointF pos2);
    void mousePressStatusNull(QGraphicsSceneMouseEvent *event);
    bool mousePressStatusNullSignal(QGraphicsSceneMouseEvent *event);
    bool mousePressStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event);
    virtual bool mousePressStatusNullItem(QGraphicsSceneMouseEvent *event);
    bool mousePressStatusNullScene(QGraphicsSceneMouseEvent *event);
    void mouseMoveStatusNull(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullSignal(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullSignalAdjust(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullItem(QGraphicsSceneMouseEvent *event);
    bool mouseMoveStatusNullScene(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusNull(QGraphicsSceneMouseEvent *event);

    void mouseMoveStatusItemMoving(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusItemMoving(QGraphicsSceneMouseEvent *event);

    void mouseReleaseStatusSceneMoving(QGraphicsSceneMouseEvent *event);

    void mouseMoveStatusSignalConnecting(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusSignalConnecting(QGraphicsSceneMouseEvent *event);

    void mouseMoveStatusSignalAdjusting(QGraphicsSceneMouseEvent *event);
    void mouseReleaseStatusSignalAdjusting(QGraphicsSceneMouseEvent *event);
};

#endif // TOOLGOPOINTEREXTEND_H
