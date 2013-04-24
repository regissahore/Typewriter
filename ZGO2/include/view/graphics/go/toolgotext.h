#ifndef TOOLGOTEXT_H
#define TOOLGOTEXT_H
/**
 * The text tool for GO graph.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"

class ItemGOText;

class ToolGOText : public ToolGOAbstract
{
public:
    ToolGOText(SceneGO *sceneGO);
    ~ToolGOText();
    void activate();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    ItemGOText *_item;
    bool _isActivated;
};

#endif // TOOLGOTEXT_H
