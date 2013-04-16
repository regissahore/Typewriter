#include <qmath.h>
#include "dialoggomarkovperiod.h"
#include "ui_dialoggomarkovperiod.h"

DialogGOMarkovPeriod::DialogGOMarkovPeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGOMarkovPeriod)
{
    ui->setupUi(this);
}

DialogGOMarkovPeriod::~DialogGOMarkovPeriod()
{
    delete ui;
}

double DialogGOMarkovPeriod::totalTime() const
{
    return this->ui->totalSpinBox->value();
}

int DialogGOMarkovPeriod::count() const
{
    return this->ui->loopSpinBox->value();
}

void DialogGOMarkovPeriod::on_confirmButton_clicked()
{
    this->accept();
}

void DialogGOMarkovPeriod::on_cancelButton_clicked()
{
    this->reject();
}

void DialogGOMarkovPeriod::on_totalSpinBox_valueChanged(double value)
{
    this->ui->intervalSpinBox->setValue(value / (this->ui->loopSpinBox->value() -  1));
}

void DialogGOMarkovPeriod::on_intervalSpinBox_valueChanged(double value)
{
    int count = (int)round(this->ui->totalSpinBox->value() / value + 1);
    if (count < 2)
    {
        count = 2;
    }
    this->ui->loopSpinBox->setValue(count);
}

void DialogGOMarkovPeriod::on_loopSpinBox_valueChanged(int value)
{
    this->ui->intervalSpinBox->setValue(this->ui->totalSpinBox->value() / (value -  1));
}

void DialogGOMarkovPeriod::on_intervalSpinBox_editingFinished()
{
    this->ui->intervalSpinBox->setValue(this->ui->totalSpinBox->value() / (this->ui->loopSpinBox->value() -  1));
}
