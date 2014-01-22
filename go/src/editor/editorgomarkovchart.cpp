#include <QGridLayout>
#include "EditorGoMarkovChart.h"
#include "ViewGoMarkovChart.h"

EditorGoMarkovChart::EditorGoMarkovChart(QWidget *parent) : EditorAbstract(parent)
{
    this->_view = new ViewGoMarkovChart(this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->_view, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_filter = tr("Go Chart Files(*.goc)");
    this->_suffix = "goc";
    this->setModified(false);
}

void EditorGoMarkovChart::bindMessage(MessageController *controller)
{
    this->MessageCreator::_messageController = controller;
}

void EditorGoMarkovChart::activate()
{
    this->_view->activate(this->MessageCreator::_messageController);
}

bool EditorGoMarkovChart::save()
{
    return this->_view->save(this->path());
}

bool EditorGoMarkovChart::tryOpen(const QString path)
{
    return this->_view->tryOpen(path);
}
