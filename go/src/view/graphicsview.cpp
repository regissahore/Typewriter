#include "GraphicsView.h"
#include "qmath.h"

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

qreal GraphicsView::zoom() const
{
    return this->_zoom;
}

void GraphicsView::setZoom(qreal value)
{
    if (this->_zoom != value)
    {
        this->_zoom = value;
        this->setupMatrix();
    }
}

void GraphicsView::setupMatrix()
{
    qreal scale = qPow(qreal(2), (this->zoom() - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    this->setMatrix(matrix);
}

void GraphicsView::zoomIn(int level)
{
    this->setZoom(this->zoom() + level);
}

void GraphicsView::zoomOut(int level)
{
    this->setZoom(this->zoom() - level);
}
