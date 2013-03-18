#ifndef VIEWGO_H
#define VIEWGO_H
/**
 * GO法的视图。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QGraphicsView>
#include "graphicsview.h"
#include "scenego.h"

class ViewGO : public GraphicsView
{
    Q_OBJECT
public:
    explicit ViewGO(QWidget *parent = 0);
    
protected:
    SceneGO *_scene; /** GO法的场景。 */
    
};

#endif // VIEWGO_H
