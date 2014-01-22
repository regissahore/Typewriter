#include <QPushButton>
#include "ToolboxAbstract.h"

ToolboxAbstract::ToolboxAbstract(QWidget *parent) : QWidget(parent)
{
    this->_selectedTool = 0L;
}

ToolboxAbstract::~ToolboxAbstract()
{
    this->Messager::~Messager();
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
