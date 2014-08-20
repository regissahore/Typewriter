#ifndef TOOLGOMARKOVCOMMONCAUSE2_H
#define TOOLGOMARKOVCOMMONCAUSE2_H
#include "stable.h"
#include "ToolGoAbstract.h"

class ItemGoMarkovOperator;
class ItemGoMarkovCommonCause;

class ToolGoMarkovCommonCause : public ToolGoAbstract
{
public:
    ToolGoMarkovCommonCause(SceneGo *sceneGo);
    ~ToolGoMarkovCommonCause();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVector<ItemGoMarkovOperator*>* operatorList() const;

private:
    enum Status
    {
        Status_Selecting,
        Status_Finishing,
        Status_Finished
    };
    Status _status;
    QVector<ItemGoMarkovOperator*> *_operatorList;
    ItemGoMarkovCommonCause *_commonItem;
    void addOperator(ItemGoMarkovOperator* op);
};

#endif // TOOLGOMARKOVCOMMONCAUSE2_H
