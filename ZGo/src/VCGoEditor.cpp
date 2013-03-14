#include "VCGoEditor.h"
#include "ui_VCGoEditor.h"

/**
 * 构造函数。
 */
VCGoEditor::VCGoEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VCGoEditor)
{
    this->ui->setupUi(this);
}

VCGoEditor::~VCGoEditor()
{
    delete ui;
}

void VCGoEditor::on_tabWidget_tabCloseRequested(int index)
{

}
