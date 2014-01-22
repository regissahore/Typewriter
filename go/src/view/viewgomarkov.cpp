#include "ViewGoMarkov.h"
#include "SceneGoMarkov.h"

ViewGoMarkov::ViewGoMarkov(QWidget *parent) : ViewGo(parent)
{
    delete this->_scene;
    this->_scene = new SceneGoMarkov(this);
    this->setScene(this->_scene);
}
