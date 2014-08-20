#include <qmath.h>
#include "DialogGoMarkovPeriod.h"
#include "ui_DialogGoMarkovPeriod.h"

DialogGoMarkovPeriod::DialogGoMarkovPeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGoMarkovPeriod)
{
    ui->setupUi(this);
}

DialogGoMarkovPeriod::~DialogGoMarkovPeriod()
{
    delete ui;
}

double DialogGoMarkovPeriod::totalTime() const
{
    return this->ui->totalSpinBox->value();
}

int DialogGoMarkovPeriod::count() const
{
    return this->ui->loopSpinBox->value();
}

void DialogGoMarkovPeriod::setTotalTime(const double value)
{
    this->ui->totalSpinBox->setValue(value);
}

void DialogGoMarkovPeriod::setCount(const int value)
{
    this->ui->loopSpinBox->setValue(value);
}

void DialogGoMarkovPeriod::on_confirmButton_clicked()
{
    this->accept();
}

void DialogGoMarkovPeriod::on_cancelButton_clicked()
{
    this->reject();
}

void DialogGoMarkovPeriod::on_totalSpinBox_valueChanged(double value)
{
    this->ui->intervalSpinBox->setValue(value / (this->ui->loopSpinBox->value() -  1));
}

void DialogGoMarkovPeriod::on_intervalSpinBox_valueChanged(double value)
{
    int count = (int)round(this->ui->totalSpinBox->value() / value + 1);
    if (count < 2)
    {
        count = 2;
    }
    this->ui->loopSpinBox->setValue(count);
}

void DialogGoMarkovPeriod::on_loopSpinBox_valueChanged(int value)
{
    this->ui->intervalSpinBox->setValue(this->ui->totalSpinBox->value() / (value -  1));
}

void DialogGoMarkovPeriod::on_intervalSpinBox_editingFinished()
{
    this->ui->intervalSpinBox->setValue(this->ui->totalSpinBox->value() / (this->ui->loopSpinBox->value() -  1));
}
