#include "view/graphicsview.h"

/**
 * 构造函数。
 * @param view 视图。
 */
GraphicsView::GraphicsView(View *view) : QGraphicsView()
{
    this->_view = view;
}

/**
 * 获取视图。
 * @return 视图。
 */
View* GraphicsView::view() const
{
    return this->_view;
}

/**
 * Ctrl键是否按下。
 * @return 如果按下返回true，否则返回false。
 */
bool GraphicsView::isCtrlPressed()
{
    return this->_ctrlPressed;
}

/**
 * 设置Ctrl键是否按下。
 * @param value 是否按下。
 */
void GraphicsView::setCtrlPressed(bool value)
{
    this->_ctrlPressed = value;
}

/**
 * 鼠标滚轮的事件。
 * @return event 滚轮事件。
 */
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (this->isCtrlPressed())
        {
            if (event->delta() > 0)
            {
                this->view()->zoomIn(6);
            }
            else
            {
                this->view()->zoomOut(6);
            }
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}

/**
 * 按键按下事件。
 * @param event 按键事件。
 */
void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::CTRL)
    {
        this->setCtrlPressed(true);
    }
}

/**
 * 按键抬起事件。
 * @param event 按键事件。
 */
void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::CTRL)
    {
        this->setCtrlPressed(false);
    }
}

/**
 * 构造函数。
 * @param parent 父窗体。
 */
View::View(QWidget *parent) : QFrame(parent)
{
    this->_graphicsView = new GraphicsView(this);
    this->_graphicsView->setRenderHints(QPainter::Antialiasing);
    this->_graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    this->_graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->_graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->_zoom = qreal(250);
    this->setupMatrix();
}

/**
 * 返回视图。
 * @return 视图。
 */
QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView*>(this->_graphicsView);
}

/**
 * 获取当前缩放的数值。
 * @return 缩放的数值。
 */
qreal View::zoom() const
{
    return this->_zoom;
}

/**
 * 设置当前缩放的数值，会触发视图的变换。
 * @param value 缩放的数值。
 */
void View::setZoom(qreal value)
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
void View::setupMatrix()
{
    qreal scale = qPow(qreal(2), (this->zoom() - 250) / qreal(50));
    QMatrix matrix;
    matrix.scale(scale, scale);
    this->_graphicsView->setMatrix(matrix);
}

/**
 * 拉近视图。
 * @param level 变化的程度。
 */
void View::zoomIn(int level)
{
    this->setZoom(this->zoom() + level);
}

/**
 * 拉远视图。
 * @param level 变化的程度。
 */
void View::zoomOut(int level)
{
    this->setZoom(this->zoom() - level);
}
