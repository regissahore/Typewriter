#ifndef TOOLGOOPERATOR_H
#define TOOLGOOPERATOR_H
/**
 * The basic operator of the GO Graph.
 * The tool is used for dragging operator to the graph.
 * After this procedure, the tool will automatically set to pointer.
 * And the current selection is the item created just now.
 * It is considered to have fixed number of input(s) and output(s) when it is not inherited.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "definationtooltype.h"
#include "messagefactorytool.h"
#include "messagefactoryeditor.h"
#include "messageeditorselection.h"
#include "toolgoabstract.h"
#include "itemgooperator.h"

class ToolGOOperator : public ToolGOAbstract
{
public:
    ToolGOOperator(SceneGO *sceneGO);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
protected:
    ItemGOOperator *_GOOperator;
};

#endif // TOOLGOOPERATOR_H
