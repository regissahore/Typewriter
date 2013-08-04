#include "viewgomarkovchart.h"
#include "scenegomarkovchart.h"

ViewGOMarkovChart::ViewGOMarkovChart(QWidget *parent) : GraphicsView(parent)
{
    this->_scene = new SceneGOMarkovChart(this);
    this->setScene(this->_scene);
}

void ViewGOMarkovChart::activate(MessageController *controller)
{
    this->_scene->activate(controller);
}

bool ViewGOMarkovChart::save(QString path)
{
    return this->_scene->save(path);
}

bool ViewGOMarkovChart::tryOpen(QString path)
{
    return this->_scene->tryOpen(path);
}
