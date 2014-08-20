#ifndef TOOLGOOPERATOR_H
#define TOOLGOOPERATOR_H
#include "DefinationToolType.h"
#include "ToolGoAbstract.h"
#include "ItemGoOperator.h"

class ToolGoOperator : public ToolGoAbstract
{
public:
    ToolGoOperator(SceneGo *sceneGo);
    ~ToolGoOperator();
    void setType(const int type);
    virtual void activate(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected:
    ItemGoOperator *_GoOperator;
    bool _isActivated;
    int _defaultToolType;
    bool getInputNumber();
    bool getOutputNumber();
    bool getDualNumber();
};

#endif // TOOLGOOPERATOR_H
