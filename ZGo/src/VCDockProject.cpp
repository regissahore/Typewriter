#include "include/VCDockProject.h"
#include "ui_VCDockProject.h"

VCDockProject::VCDockProject(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCDockProject)
{
    ui->setupUi(this);
}

VCDockProject::~VCDockProject()
{
    delete ui;
}
