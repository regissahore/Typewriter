#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
/**
 * 基本的GraphicsView。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <qmath.h>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QGraphicsView>

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent);
    qreal zoom() const;
    void setZoom(qreal value);
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

protected:
    //View *view() const;
    void setupMatrix();
    void wheelEvent(QWheelEvent *event);

private:
    qreal _zoom;
};

#endif // GRAPHICSVIEW_H
