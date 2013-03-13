#include "include/VCWidgetEditor.h"
#include "ui_VCWidgetEditor.h"

VCWidgetEditor::VCWidgetEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCWidgetEditor)
{
    ui->setupUi(this);
}

VCWidgetEditor::~VCWidgetEditor()
{
    delete ui;
}
