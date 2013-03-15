#include "view/scenego.h"

SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent)
{
    //以下为测试内容。
    ItemGOOperator *go = new ItemGOOperator();
    GOOperator *model = new GOOperator();
    model->setType(19);
    model->setId(627);
    model->setName("Test");
    model->input()->setNumber(3);
    model->subInput()->setNumber(1);
    model->output()->setNumber(6);
    go->setModel(model);
    this->addItem(go);
}
