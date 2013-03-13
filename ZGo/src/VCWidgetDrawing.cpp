#include "include/VCWidgetDrawing.h"
#include "ui_VCWidgetDrawing.h"

VCWidgetDrawing::VCWidgetDrawing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCWidgetDrawing)
{
    ui->setupUi(this);
}

VCWidgetDrawing::~VCWidgetDrawing()
{
    delete ui;
}
