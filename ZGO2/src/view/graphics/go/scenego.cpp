#include "scenego.h"

SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent)
{
    //以下为测试内容。
    ItemGOOperator *go = new ItemGOOperator();
    GOOperator *model = new GOOperator();
    model->setType(19);
    model->setId(627);
    model->setName("Medium");
    model->input()->setNumber(3);
    model->subInput()->setNumber(1);
    model->output()->setNumber(6);
    go->setModel(model);
    this->addItem(go);
    ItemGOSource  *go2 = new ItemGOSource();
    GOOperator *model2 = new GOOperator();
    model2->setType(7);
    model2->setId(2);
    model2->setName("Source");
    model2->output()->setNumber(3);
    go2->setModel(model2);
    go2->setPos(100, 100);
    this->addItem(go2);
}
