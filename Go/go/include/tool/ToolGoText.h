#ifndef TOOLGOTEXT_H
#define TOOLGOTEXT_H
#include "ToolGoAbstract.h"

class ItemGoText;

class ToolGoText : public ToolGoAbstract
{
public:
    ToolGoText(SceneGo *sceneGo);
    ~ToolGoText();
    void activate(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    ItemGoText *_item;
    bool _isActivated;
    int _defaultToolType;
};

#endif // TOOLGOTEXT_H
