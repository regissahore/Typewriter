#include "VCGoDockTool.h"
#include "ui_VCGoDockTool.h"

VCGoDockTool::VCGoDockTool(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCGoDockTool)
{
    ui->setupUi(this);
}

VCGoDockTool::~VCGoDockTool()
{
    delete ui;
}
