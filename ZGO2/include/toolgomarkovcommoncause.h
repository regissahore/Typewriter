#ifndef TOOLGOMARKOVCOMMONCAUSE_H
#define TOOLGOMARKOVCOMMONCAUSE_H
/**
 * The tool for setting the common cause of GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "toolgoselect.h"

class ToolGOMarkovCommonCause : public ToolGOSelect
{
public:
    ToolGOMarkovCommonCause(SceneGO *sceneGO);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected:
    void addCommonCause();
};

#endif // TOOLGOMARKOVCOMMONCAUSE_H
