#ifndef SCENEGO_H
#define SCENEGO_H
#include <QSharedPointer>
#include <QGraphicsScene>
#include "DomItem.h"
#include "Messager.h"

class Message;
class ToolGoAbstract;
class GoGraph;
class ItemEmpty;
class ViewGo;

class SceneGo : public QGraphicsScene, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit SceneGo(QObject *parent = 0);
    ~SceneGo();
    void selectTool(int type);
    void messageEvent(QSharedPointer<Message> message);
    QSharedPointer<GoGraph> generateGoGraph();
    virtual void analysisProbability(const QString filePath);
    virtual void analysisPath(const QString filePath);
    virtual void analysisCut(const QString filePath);
    void extendEdge(float x, float y);
    ViewGo* viewGo() const;
    void save(QDomDocument &document, QDomElement &root) override;
    bool tryOpen(QDomElement &root) override;

protected:
    ToolGoAbstract *_tool;
    ItemEmpty *_emptyTopLeft;
    ItemEmpty *_emptyBottomRight;
    ViewGo *_viewGo;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SCENEGO_H
