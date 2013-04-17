#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "scenegomarkovchart.h"
#include "gomarkovchartdata.h"
#include "itemgomarkovchart.h"

SceneGOMarkovChart::SceneGOMarkovChart(QObject *parent) : QGraphicsScene(parent)
{
    this->_chartData = new GOMarkovChartData();
    this->_chartItem = new ItemGOMarkovChart();
    this->_chartItem->setPos(50, 50);
    this->addItem(this->_chartItem);
}

SceneGOMarkovChart::~SceneGOMarkovChart()
{
    this->removeItem(this->_chartItem);
    delete this->_chartItem;
    delete this->_chartData;
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
