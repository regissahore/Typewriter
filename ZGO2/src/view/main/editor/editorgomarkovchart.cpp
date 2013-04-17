#include <QGridLayout>
#include "editorgomarkovchart.h"
#include "viewgomarkovchart.h"

EditorGOMarkovChart::EditorGOMarkovChart(QWidget *parent) : EditorAbstract(parent)
{
    this->_view = new ViewGOMarkovChart(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->_view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("GO Chart Files(*.goc)");
    this->setModified(false);
}

bool EditorGOMarkovChart::save()
{
    return this->_view->save(this->path());
}

bool EditorGOMarkovChart::tryOpen(const QString path)
{
    return this->_view->tryOpen(path);
}
