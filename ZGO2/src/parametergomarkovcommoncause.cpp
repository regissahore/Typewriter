#include <QLabel>
#include <QDoubleSpinBox>
#include "parametergomarkovcommoncause.h"
#include "itemgomarkovcommoncause.h"
#include "gomarkovcommoncause.h"

ParameterGOMarkovCommonCause::ParameterGOMarkovCommonCause(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOMarkovCommonCause::bindItem(void *item)
{
    this->_item = item;
    if (0L != this->_item)
    {
        ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
        QDoubleSpinBox *spin;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Total"), this));
        spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(12);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->breakdownTotal());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBreakdownTotal(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Individual"), this));
        spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(12);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->breakdownIndividual());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemBreakdownIndividual(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Gamma C"), this));
        spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1e100);
        spin->setDecimals(12);
        spin->setSingleStep(0.01);
        spin->setValue(item->model()->gammaC());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemGammaC(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovCommonCause::setItemBreakdownTotal(double value)
{
    ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
    item->model()->setBreakdownTotal(value);
}

void ParameterGOMarkovCommonCause::setItemBreakdownIndividual(double value)
{
    ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
    item->model()->setBreakdownIndividual(value);
}

void ParameterGOMarkovCommonCause::setItemGammaC(double value)
{
    ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
    item->model()->setGammaC(value);
}
