#include "toolboxnull.h"

ToolboxNull::ToolboxNull(QWidget *parent) : ToolboxAbstract(parent)
{
    QLabel *label = new QLabel(tr("No tool. "), this);
    QGridLayout *layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(label);
    this->setLayout(layout);
}



