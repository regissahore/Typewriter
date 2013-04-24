#include "editorgomarkov.h"
#include "viewgomarkov.h"

EditorGOMarkov::EditorGOMarkov(QWidget *parent) : EditorGO(parent)
{
    delete this->_view;
    this->_view = new ViewGOMarkov(this);
    this->layout()->addWidget(this->_view);
    this->_filter = tr("GO Markov Files(*.gom)");
    this->_suffix = "gom";
}
