#include "ViewGoMarkovChart.h"
#include "SceneGoMarkovChart.h"

ViewGoMarkovChart::ViewGoMarkovChart(QWidget *parent) : GraphicsView(parent)
{
    this->_scene = new SceneGoMarkovChart(this);
    this->setScene(this->_scene);
}

void ViewGoMarkovChart::activate(MessageController *controller)
{
    this->_scene->activate(controller);
}

bool ViewGoMarkovChart::save(QString path)
{
    return this->_scene->save(path);
}

bool ViewGoMarkovChart::tryOpen(QString path)
{
    return this->_scene->tryOpen(path);
}
