#ifndef VIEWGO_H
#define VIEWGO_H
#include <QGraphicsView>
#include "graphicsview.h"
#include "scenego.h"
#include "messager.h"
#include "domitem.h"

class EditorGO;

class ViewGO : public GraphicsView, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit ViewGO(QWidget *parent = 0);
    ~ViewGO();
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    EditorGO* editor() const;
    
protected:
    SceneGO *_scene; /** GO法的场景。 */
    EditorGO *_editor;
};

#endif // VIEWGO_H
