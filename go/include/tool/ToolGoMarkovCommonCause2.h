#ifndef TOOLGOMARKOVCOMMONCAUSE2_H
#define TOOLGOMARKOVCOMMONCAUSE2_H
#include <QVector>
#include "ToolGoAbstract.h"

class ItemGoMarkovOperator;
class ItemGoMarkovCommonCause2;

class ToolGoMarkovCommonCause2 : public ToolGoAbstract
{
public:
    ToolGoMarkovCommonCause2(SceneGo *sceneGo);
    ~ToolGoMarkovCommonCause2();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVector<ItemGoMarkovOperator*>* operatorList() const;

private:
    enum Status
    {
        Status_Selecting,   /** 选择操作符。*/
        Status_Finishing,   /** 放置共因失效。*/
        Status_Finished
    };
    Status _status;
    QVector<ItemGoMarkovOperator*> *_operatorList;
    ItemGoMarkovCommonCause2 *_commonItem;
    void addOperator(ItemGoMarkovOperator* op);
};

#endif // TOOLGOMARKOVCOMMONCAUSE2_H
