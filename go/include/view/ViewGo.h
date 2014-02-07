#ifndef VIEWGO_H
#define VIEWGO_H
#include <memory>
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
    void messageEvent(std::shared_ptr<Message> message);
    void save(QDomDocument &document, QDomElement &root);
    bool tryOpen(QDomElement &root);
    EditorGo* editor() const;
    
protected:
    SceneGo *_scene; /** Go法的场景。 */
    EditorGo *_editor;
};

#endif // VIEWGO_H
