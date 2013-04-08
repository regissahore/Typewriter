#include "editorgomarkov.h"

EditorGOMarkov::EditorGOMarkov(QWidget *parent) : EditorGO(parent)
{
    this->view = new ViewGO(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("GO Markov Files(*.gom)");
}
