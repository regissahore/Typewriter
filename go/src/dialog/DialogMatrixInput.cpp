#include "DialogMatrixInput.h"
#include "ui_DialogMatrixInput.h"

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

QTableWidget* DialogMatrixInput::table() const
{
    return this->ui->tableData;
}
