#include "VCGoDockProject.h"
#include "ui_VCGoDockProject.h"

VCGoDockProject::VCGoDockProject(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCGoDockProject)
{
    ui->setupUi(this);
}

VCGoDockProject::~VCGoDockProject()
{
    delete ui;
}
