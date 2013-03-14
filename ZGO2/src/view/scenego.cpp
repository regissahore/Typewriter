#include "view/scenego.h"

SceneGO::SceneGO(QObject *parent) : QGraphicsScene(parent)
{
    //以下为测试内容。
    this->addText("Test");
    this->addLine(0, 0, 500, 500);
}
