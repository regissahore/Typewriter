#include <QPushButton>
#include "toolboxabstract.h"

ToolboxAbstract::ToolboxAbstract(QWidget *parent) : QWidget(parent)
{
    this->_selectedTool = 0L;
}

ToolboxAbstract::~ToolboxAbstract()
{
    this->MessageListener::~MessageListener();
}

void ToolboxAbstract::setSelectedTool(QPushButton *tool)
{
    if (this->_selectedTool != 0L)
    {
        this->_selectedTool->setEnabled(true);
    }
    this->_selectedTool = tool;
    this->_selectedTool->setEnabled(false);
}
