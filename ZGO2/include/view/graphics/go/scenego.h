#ifndef SCENEGO_H
#define SCENEGO_H

#include <QGraphicsScene>
#include "domitem.h"
#include "messager.h"

class Message;
class ToolGOAbstract;

class SceneGO : public QGraphicsScene, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit SceneGO(QObject *parent = 0);
    ~SceneGO();
    void selectTool(int type);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);

protected:
    ToolGOAbstract *_tool;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENEGO_H
