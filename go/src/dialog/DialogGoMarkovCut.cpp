#include "DialogGoMarkovCut.h"
#include "ui_DialogGoMarkovCut.h"

DialogGoMarkovCut::DialogGoMarkovCut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGoMarkovCut)
{
    ui->setupUi(this);
}

DialogGoMarkovCut::~DialogGoMarkovCut()
{
    delete ui;
}

double DialogGoMarkovCut::interval() const
{
    return this->ui->spinInterval->value();
}

int DialogGoMarkovCut::count() const
{
    return this->ui->spinCount->value();
}

int DialogGoMarkovCut::order() const
{
    return this->ui->spinOrder->value();
}

void DialogGoMarkovCut::on_buttonConfirm_clicked()
{
    this->accept();
}

void DialogGoMarkovCut::on_buttonCancel_clicked()
{
    this->reject();
}
