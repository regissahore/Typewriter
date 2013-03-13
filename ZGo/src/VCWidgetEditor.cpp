#include "VCWidgetEditor.h"
#include "ui_VCWidgetEditor.h"

VCWidgetEditor::VCWidgetEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCWidgetEditor)
{
    this->ui->setupUi(this);
}

VCWidgetEditor::~VCWidgetEditor()
{
    delete ui;
}
