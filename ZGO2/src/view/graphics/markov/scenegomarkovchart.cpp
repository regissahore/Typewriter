#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "scenegomarkovchart.h"
#include "gomarkovchartdata.h"
#include "itemgomarkovchart.h"
#include "itemarrow.h"

SceneGOMarkovChart::SceneGOMarkovChart(QObject *parent) : QGraphicsScene(parent)
{
    this->_chartData = new GOMarkovChartData();
    this->_chartItem = new ItemGOMarkovChart();
    this->_chartItem->setPos(50, 50);
    this->addItem(this->_chartItem);
    this->_leftArrow = new ItemArrow();
    this->_leftArrow->setPos(430, 600);
    this->_leftArrow->setEnd(-30, 0);
    this->addItem(this->_leftArrow);
    this->_rightArrow = new ItemArrow();
    this->_rightArrow->setPos(470, 600);
    this->_rightArrow->setEnd(30, 0);
    this->addItem(this->_rightArrow);
    this->_leftText = new QGraphicsTextItem(tr("Prev"));
    this->_leftText->setPos(400, 600);
    this->addItem(this->_leftText);
    this->_rightText = new QGraphicsTextItem(tr("Next"));
    this->_rightText->setPos(470, 600);
    this->addItem(this->_rightText);
}

SceneGOMarkovChart::~SceneGOMarkovChart()
{
    delete this->_chartItem;
    delete this->_chartData;
    delete this->_leftArrow;
    delete this->_rightArrow;
    delete this->_leftText;
    delete this->_rightText;
}

bool SceneGOMarkovChart::save(QString path)
{
    return this->_chartData->save(path);
}

bool SceneGOMarkovChart::tryOpen(QString path)
{
    if (this->_chartData->tryOpen(path))
    {
        this->_chartItem->setTime(this->_chartData->times);
        if (this->_chartData->ids.size() > 0)
        {
            this->selectOperator(0);
        }
        return true;
    }
    return false;
}

void SceneGOMarkovChart::selectOperator(int index)
{
    this->_currentIndex = index;
    this->_chartItem->setTitle(QString("%1 - %2").arg(this->_chartData->types[index]).arg(this->_chartData->ids[index]));
    this->_chartItem->setProbability(this->_chartData->probabilities[index]);
}

void SceneGOMarkovChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->_chartItem->setDetailIndex(event->scenePos().x(), event->scenePos().y());
}

void SceneGOMarkovChart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> items = this->items(QRectF(event->scenePos().x() - 5, event->scenePos().y() - 5, 10, 10));
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i] == this->_leftArrow || items[i] == this->_leftText)
        {
            --this->_currentIndex;
            if (this->_currentIndex < 0)
            {
                this->_currentIndex = this->_chartData->ids.size() - 1;
            }
            this->selectOperator(this->_currentIndex);
        }
        else if (items[i] == this->_rightArrow || items[i] == this->_rightText)
        {
            ++this->_currentIndex;
            if (this->_currentIndex >= this->_chartData->ids.size())
            {
                this->_currentIndex = 0;
            }
            this->selectOperator(this->_currentIndex);
        }
    }
}

void SceneGOMarkovChart::keyReleaseEvent(QKeyEvent *event)
{
    if (this->_chartData->ids.size() > 0)
    {
        if (event->key() == Qt::Key_Left)
        {
            --this->_currentIndex;
            if (this->_currentIndex < 0)
            {
                this->_currentIndex = this->_chartData->ids.size() - 1;
            }
            this->selectOperator(this->_currentIndex);
        }
        else if (event->key() == Qt::Key_Right)
        {
            ++this->_currentIndex;
            if (this->_currentIndex >= this->_chartData->ids.size())
            {
                this->_currentIndex = 0;
            }
            this->selectOperator(this->_currentIndex);
        }
    }
}
