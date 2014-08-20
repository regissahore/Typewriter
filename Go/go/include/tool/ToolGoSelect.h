#ifndef TOOLGOSELECT_H
#define TOOLGOSELECT_H
#include "ToolGoAbstract.h"
#include "ItemSelection.h"

class ToolGoSelect : public ToolGoAbstract
{
public:
    ToolGoSelect(SceneGo *sceneGo);
    ~ToolGoSelect();
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
    void selectAll();
    void copy();
    void setGlobalFeedback();
    void unsetGlobalFeedback();
    void setShowParameter();
    void setHideParameter();
};

#endif // TOOLGOSELECT_H
