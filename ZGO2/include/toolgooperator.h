#ifndef TOOLGOOPERATOR_H
#define TOOLGOOPERATOR_H
#include "definationtooltype.h"
#include "toolgoabstract.h"
#include "itemgooperator.h"

class ToolGOOperator : public ToolGOAbstract
{
public:
    ToolGOOperator(SceneGO *sceneGO);
    ~ToolGOOperator();
    void setType(const int type);
    virtual void activate(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    ItemGOOperator *_GOOperator;
    bool _isActivated;
    int _defaultToolType;
    bool getInputNumber();
    bool getOutputNumber();
    bool getDualNumber();
};

#endif // TOOLGOOPERATOR_H
