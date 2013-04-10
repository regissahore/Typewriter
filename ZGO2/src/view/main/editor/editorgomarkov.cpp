#include "editorgomarkov.h"
#include "viewgomarkov.h"

EditorGOMarkov::EditorGOMarkov(QWidget *parent) : EditorGO(parent)
{
    delete this->view;
    this->view = new ViewGOMarkov(this);
    this->layout()->addWidget(this->view);
    this->_filter = tr("GO Markov Files(*.gom)");
}
