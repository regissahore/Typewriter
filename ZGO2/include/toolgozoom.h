#ifndef TOOLGOZOOM_H
#define TOOLGOZOOM_H
/**
 * The zoom tool of the GO graph.
 * It is zoom out when ALT is pressed.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoabstract.h"

class ToolGOZoom : public ToolGOAbstract
{
public:
    ToolGOZoom(SceneGO *sceneGO);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TOOLGOZOOM_H
