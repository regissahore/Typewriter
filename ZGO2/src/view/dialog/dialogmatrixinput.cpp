#include "dialogmatrixinput.h"
#include "ui_dialogmatrixinput.h"

DialogMatrixInput::DialogMatrixInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMatrixInput)
{
    ui->setupUi(this);
    this->connect(this->ui->buttonConfirm, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(this->ui->buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

DialogMatrixInput::~DialogMatrixInput()
{
    delete ui;
}

