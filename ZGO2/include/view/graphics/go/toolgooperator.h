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
#include "toolgoabstract.h"
#include "itemgooperator.h"

class ToolGOOperator : public ToolGOAbstract
{
public:
    ToolGOOperator(SceneGO *sceneGO);
    ~ToolGOOperator();
    void setType(const int type);
    void activate(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    ItemGOOperator *_GOOperator;
    bool _isActivated;
    int _defaultToolType;
    void getInputNumber();
    void getOutputNumber();
};

#endif // TOOLGOOPERATOR_H
