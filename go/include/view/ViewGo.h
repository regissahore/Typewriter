#ifndef VIEWGO_H
#define VIEWGO_H
#include <QSharedPointer>
#include <QGraphicsView>
#include "GraphicsView.h"
#include "SceneGo.h"
#include "Messager.h"
#include "DomItem.h"

class EditorGo;

class ViewGo : public GraphicsView, public Messager, public DomItem
{
    Q_OBJECT
public:
    explicit ViewGo(QWidget *parent = 0);
    ~ViewGo();
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    EditorGo* editor() const;
    
protected:
    SceneGo *_scene; /** Go法的场景。 */
    EditorGo *_editor;
};

#endif // VIEWGO_H
