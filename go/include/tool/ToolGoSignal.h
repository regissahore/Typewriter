#ifndef TOOLGOSIGNAL_H
#define TOOLGOSIGNAL_H
#include "ToolGoAbstract.h"

class ItemGoSignal;

class ToolGoSignal : public ToolGoAbstract
{
public:
    ToolGoSignal(SceneGo *sceneGo);
    ~ToolGoSignal();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    enum Status
    {
        Status_Null,
        Status_Adding
    };
    Status _status;
    ItemGoSignal *_tempSignal;
    bool isAround(QPointF pos1, QPointF pos2);
};

#endif // TOOLGOSIGNAL_H
