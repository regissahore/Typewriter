#ifndef TOOLGOMARKOVCOMMONCAUSE2_H
#define TOOLGOMARKOVCOMMONCAUSE2_H
/**
 * 添加共因失效的工具。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include "toolgoabstract.h"

class ItemGOMarkovOperator;
class ItemGOMarkovCommonCause2;

class ToolGOMarkovCommonCause2 : public ToolGOAbstract
{
public:
    ToolGOMarkovCommonCause2(SceneGO *sceneGO);
    ~ToolGOMarkovCommonCause2();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVector<ItemGOMarkovOperator*>* operatorList() const;

private:
    enum Status
    {
        Status_Selecting,   /** 选择操作符。*/
        Status_Finishing,   /** 放置共因失效。*/
        Status_Finished
    };
    Status _status;
    QVector<ItemGOMarkovOperator*> *_operatorList;
    ItemGOMarkovCommonCause2 *_commonItem;
    void addOperator(ItemGOMarkovOperator* op);
};

#endif // TOOLGOMARKOVCOMMONCAUSE2_H
