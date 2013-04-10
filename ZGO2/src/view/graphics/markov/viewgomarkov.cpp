#include "viewgomarkov.h"
#include "scenegomarkov.h"

ViewGOMarkov::ViewGOMarkov(QWidget *parent) : ViewGO(parent)
{
    delete this->_scene;
    this->_scene = new SceneGOMarkov(this);
    this->setScene(this->_scene);
}
