#include "include/VCDockParameter.h"
#include "ui_VCDockParameter.h"

VCDockParameter::VCDockParameter(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCDockParameter)
{
    ui->setupUi(this);
}

VCDockParameter::~VCDockParameter()
{
    delete ui;
}
