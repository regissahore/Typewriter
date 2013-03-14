#include "VCGoDockParameter.h"
#include "ui_VCGoDockParameter.h"

VCGoDockParameter::VCGoDockParameter(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCGoDockParameter)
{
    ui->setupUi(this);
}

VCGoDockParameter::~VCGoDockParameter()
{
    delete ui;
}
