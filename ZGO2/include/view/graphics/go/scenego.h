#ifndef SCENEGO_H
#define SCENEGO_H

#include <QGraphicsScene>
#include "messager.h"
#include "itemgooperator.h"
#include "itemgosource.h"
#include "toolgofactory.h"
#include "messagefactorytool.h"

class SceneGO : public QGraphicsScene, public Messager
{
    Q_OBJECT
public:
    explicit SceneGO(QObject *parent = 0);
    void selectTool(int type);
    void bindMessage(MessageController *controller);

protected:
    ToolGOAbstract *_tool;
    void messageEvent(Message *message);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENEGO_H
