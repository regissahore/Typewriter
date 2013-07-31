#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
/**
 * The basic graphics view。
 * @author ZHG <CyberZHG@gmail.com>
 */
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
    void zoomIn(int level = 5);
    void zoomOut(int level = 5);

protected:
    void setupMatrix();
    void wheelEvent(QWheelEvent *event);

private:
    qreal _zoom;
};

#endif // GRAPHICSVIEW_H
