#include "include/VCDockTool.h"
#include "ui_VCDockTool.h"

VCDockTool::VCDockTool(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCDockTool)
{
    ui->setupUi(this);
}

VCDockTool::~VCDockTool()
{
    delete ui;
}
