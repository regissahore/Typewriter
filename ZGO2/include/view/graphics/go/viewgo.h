#ifndef VIEWGO_H
#define VIEWGO_H
/**
 * The view of the GO graph。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsView>
#include "graphicsview.h"
#include "scenego.h"
#include "messager.h"
#include "domitem.h"

class ViewGO : public GraphicsView, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit ViewGO(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    
protected:
    SceneGO *_scene; /** GO法的场景。 */
};

#endif // VIEWGO_H
