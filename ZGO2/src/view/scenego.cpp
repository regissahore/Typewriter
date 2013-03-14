#include "view/scenego.h"

SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent)
{
    //以下为测试内容。
    this->addItem(new ItemMoveable());
}
