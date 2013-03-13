#include "include/VCGoEditorTab.h"
#include "ui_VCGoEditorTab.h"

VCGoEditorTab::VCGoEditorTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCGoEditorTab)
{
    ui->setupUi(this);
}

VCGoEditorTab::~VCGoEditorTab()
{
    delete ui;
}
