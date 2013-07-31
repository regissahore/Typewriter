#ifndef TOOLGOSIGNAL_H
#define TOOLGOSIGNAL_H
/**
 * The signal tool of GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"

class ItemGOSignal;

class ToolGOSignal : public ToolGOAbstract
{
public:
    ToolGOSignal(SceneGO *sceneGO);
    ~ToolGOSignal();
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
    ItemGOSignal *_tempSignal;
    bool isAround(QPointF pos1, QPointF pos2);
};

#endif // TOOLGOSIGNAL_H
