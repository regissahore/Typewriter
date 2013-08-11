#ifndef TOOLGOSELECT_H
#define TOOLGOSELECT_H
/**
 * The select tool of GO graph.
 * Select multiple items.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"
#include "itemselection.h"

class ToolGOSelect : public ToolGOAbstract
{
public:
    ToolGOSelect(SceneGO *sceneGO);
    ~ToolGOSelect();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    enum Status
    {
        Status_Null,
        Status_Selecting,
        Status_Selected,
        Status_Moving
    };
    Status _status;
    ItemSelection *_selection;
    QList<QGraphicsItem *> _items;
    void copy();
};

#endif // TOOLGOSELECT_H
