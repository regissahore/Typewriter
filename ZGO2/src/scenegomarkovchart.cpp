#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "scenegomarkovchart.h"
#include "gomarkovchartdata.h"
#include "itemgomarkovchart.h"
#include "itemarrow.h"
#include "messagecontroller.h"
#include "messagefactory.h"

SceneGOMarkovChart::SceneGOMarkovChart(QObject *parent) : QGraphicsScene(parent)
{
    this->_chartData = new GOMarkovChartData();
    this->_chartItem = new ItemGOMarkovChart();
    this->_chartItem->setPos(50, 50);
    this->addItem(this->_chartItem);
    this->_chartItem->setChart(this->_chartData);
}

SceneGOMarkovChart::~SceneGOMarkovChart()
{
    delete this->_chartItem;
    delete this->_chartData;
}

void SceneGOMarkovChart::activate(MessageController *controller)
{
    QSharedPointer<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(this->_chartItem);
    controller->send(message);
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
        if (this->_chartData->names.size() > 0)
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
    this->_chartItem->setDisplayItem(index);
}

void SceneGOMarkovChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->_chartItem->setDetailIndex(event->scenePos().x(), event->scenePos().y());
}
