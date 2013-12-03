#ifndef SCENEGO_H
#define SCENEGO_H

#include <QGraphicsScene>
#include "domitem.h"
#include "messager.h"

class Message;
class ToolGOAbstract;
class GOGraph;
class ItemEmpty;
class ViewGO;

class SceneGO : public QGraphicsScene, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit SceneGO(QObject *parent = 0);
    ~SceneGO();
    void selectTool(int type);
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    virtual GOGraph* generatorGOGraph();
    virtual void analysisProbability(const QString filePath);
    void analysisPath(const QString filePath);
    virtual void analysisCut(const QString filePath);
    void extendEdge(float x, float y);
    ViewGO* viewGO() const;

protected:
    ToolGOAbstract *_tool;
    ItemEmpty *_emptyTopLeft;
    ItemEmpty *_emptyBottomRight;
    ViewGO *_viewGO;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENEGO_H
