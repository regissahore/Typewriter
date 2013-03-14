#include "VCGoDrawing.h"
#include "ui_VCGoDrawing.h"

VCGoDrawing::VCGoDrawing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCGoDrawing)
{
    ui->setupUi(this);
}

VCGoDrawing::~VCGoDrawing()
{
    delete ui;
}
