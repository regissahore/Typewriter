#include "toolboxnull.h"

/**
 * 构造函数。
 * @param parent 父窗体。
 */
ToolboxNull::ToolboxNull(QWidget *parent) : ToolboxAbstract(parent)
{
    QLabel *label = new QLabel(tr("No tool. "));
    QGridLayout *layout = new QGridLayout(parent);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(label);
    this->setLayout(layout);
}

ToolboxNull::~ToolboxNull()
{
}


