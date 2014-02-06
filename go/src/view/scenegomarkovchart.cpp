#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "SceneGoMarkovChart.h"
#include "GoMarkovChartData.h"
#include "ItemGoMarkovChart.h"
#include "ItemArrow.h"
#include "MessageController.h"
#include "MessageFactory.h"
using namespace std;

SceneGoMarkovChart::SceneGoMarkovChart(QObject *parent) : QGraphicsScene(parent)
{
    this->_chartData = new GoMarkovChartData();
    this->_chartItem = new ItemGoMarkovChart();
    this->_chartItem->setPos(50, 50);
    this->addItem(this->_chartItem);
    this->_chartItem->setChart(this->_chartData);
}

SceneGoMarkovChart::~SceneGoMarkovChart()
{
    delete this->_chartItem;
    delete this->_chartData;
}

void SceneGoMarkovChart::activate(MessageController *controller)
{
    shared_ptr<Message> message = MessageFactory::produce(MessageFactory::TYPE_EDITOR_SELECTION);
    message->setMessage(this->_chartItem);
    controller->send(message);
}

bool SceneGoMarkovChart::save(QString path)
{
    return this->_chartData->save(path);
}

bool SceneGoMarkovChart::tryOpen(QString path)
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

void SceneGoMarkovChart::selectOperator(int index)
{
    this->_currentIndex = index;
    this->_chartItem->setDisplayItem(index);
}

void SceneGoMarkovChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->_chartItem->setDetailIndex(event->scenePos().x(), event->scenePos().y());
}
