#include "graphicsview.h"
#include "qmath.h"

/**
 * Constructor.
 * @param parent The parent widget.
 */
GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing);
    //this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setZoom(250);
    this->setupMatrix();
}

/**
 * 鼠标滚轮的事件。
 * @return event 滚轮事件。
 */
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->delta() > 0)
        {
            this->zoomIn(6);
        }
        else
        {
            this->zoomOut(6);
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

/**
 * 获取当前缩放的数值。
 * @return 缩放的数值。
 */
qreal GraphicsView::zoom() const
{
    return this->_zoom;
}

/**
 * 设置当前缩放的数值，会触发视图的变换。
 * @param value 缩放的数值。
 */
void GraphicsView::setZoom(qreal value)
{
    if (this->_zoom != value)
    {
        this->_zoom = value;
        this->setupMatrix();
    }
}

/**
 * 设置视图变换矩阵。
 */
void GraphicsView::setupMatrix()
{
    qreal scale = qPow(qreal(2), (this->zoom() - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    this->setMatrix(matrix);
}

/**
 * 拉近视图。
 * @param level 变化的程度。
 */
void GraphicsView::zoomIn(int level)
{
    this->setZoom(this->zoom() + level);
}

/**
 * 拉远视图。
 * @param level 变化的程度。
 */
void GraphicsView::zoomOut(int level)
{
    this->setZoom(this->zoom() - level);
}
