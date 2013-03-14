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
    GraphicsView(View *view);

protected:
    View *view() const;
    bool isCtrlPressed();
    void setCtrlPressed(bool value);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    View *_view; /** 用于现实的视图。 */
    bool _ctrlPressed; /** Ctrl键是否按下。 */
};

class View : public QFrame
{
    Q_OBJECT
public:
    View(QWidget *parent);
    QGraphicsView *view() const;
    qreal zoom() const;
    void setZoom(qreal value);

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);

private slots:
    void setupMatrix();

private:
    GraphicsView *_graphicsView;
    qreal _zoom;
};

#endif // GRAPHICSVIEW_H
