#include <QLabel>
#include <QDoubleSpinBox>
#include "ParameterGoMarkovCommonCause.h"
#include "ItemGoMarkovCommonCause.h"
#include "GoMarkovCommonCause.h"

ParameterGoMarkovCommonCause::ParameterGoMarkovCommonCause(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGoMarkovCommonCause::bindItem(void *item)
{
    this->_item = item;
    if (nullptr != this->_item)
    {
        ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
        QDoubleSpinBox *spin;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Total"), this));
        this->_spinBoxTotal = new QDoubleSpinBox(this);
        spin = this->_spinBoxTotal;
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->breakdownTotal());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBreakdownTotal(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Individual"), this));
        this->_spinBoxIndividual = new QDoubleSpinBox(this);
        spin = this->_spinBoxIndividual;
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->breakdownIndividual());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBreakdownIndividual(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Common"), this));
        this->_spinBoxCommon = new QDoubleSpinBox(this);
        spin = this->_spinBoxCommon;
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->breakdownCommon());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBreakdownCommon(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Belta"), this));
        this->_spinBoxBelta = new QDoubleSpinBox(this);
        spin = this->_spinBoxBelta;
        spin->setMinimum(0.0);
        spin->setMaximum(1.0);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->belta());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBelta(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Gamma C"), this));
        this->_spinBoxGammaC = new QDoubleSpinBox(this);
        spin = this->_spinBoxGammaC;
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->gammaC());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemGammaC(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovCommonCause::setItemBreakdownTotal(double value)
{
    ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
    item->model()->setBreakdownTotal(value);
}

void ParameterGoMarkovCommonCause::setItemBreakdownIndividual(double value)
{
    ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
    item->model()->setBreakdownIndividual(value);
}

void ParameterGoMarkovCommonCause::setItemBreakdownCommon(double value)
{
    ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
    item->model()->setBreakdownCommon(value);
}

void ParameterGoMarkovCommonCause::setItemBelta(double value)
{
    ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
    item->model()->setBelta(value);
    this->_spinBoxCommon->setValue(item->model()->breakdownCommon());
    this->_spinBoxIndividual->setValue(item->model()->breakdownIndividual());
}

void ParameterGoMarkovCommonCause::setItemGammaC(double value)
{
    ItemGoMarkovCommonCause *item = (ItemGoMarkovCommonCause*)this->_item;
    item->model()->setGammaC(value);
}
