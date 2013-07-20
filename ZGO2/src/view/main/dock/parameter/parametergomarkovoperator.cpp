#include <QLabel>
#include <QDoubleSpinBox>
#include "parametergomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "gooperatorfactory.h"
#include "gomarkovstatus.h"
#include "gostatus.h"
#include "messagefactory.h"
#include "goparameter.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator9a.h"
#include "gomarkovoperator13.h"
#include "dialog13ainput.h"

ParameterGOMarkovOperator::ParameterGOMarkovOperator(QWidget *parent) : ParameterGOOperator(parent)
{
}

void ParameterGOMarkovOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
    switch (op->model()->type())
    {
    case GOMarkovOperatorFactory::Operator_Type_1:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_5:
        this->addMarkovParameter();
        break;
    default:
        break;
    }
}

void ParameterGOMarkovOperator::addTypeParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Type"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(GOMarkovOperatorFactory::typeName(item->model()->type()), this));
    }
}

void ParameterGOMarkovOperator::addMarkovParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Failure Rate"), this));
        this->_spinBoxFrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFrequencyBreakdown->setMaximum(1e100);
        this->_spinBoxFrequencyBreakdown->setDecimals(6);
        this->_spinBoxFrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFrequencyBreakdown->setValue(((GOMarkovOperator*)item->model())->markovStatus()->frequencyBreakdown());
        this->connect(this->_spinBoxFrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyBreakdown(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxFrequencyBreakdown);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Rate"), this));
        this->_spinBoxFrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFrequencyRepair->setMaximum(1e100);
        this->_spinBoxFrequencyRepair->setDecimals(6);
        this->_spinBoxFrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFrequencyRepair->setValue(((GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair());
        this->connect(this->_spinBoxFrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyRepair(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxFrequencyRepair);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Time"), this));
        this->_spinBoxRepairTime = new QDoubleSpinBox(this);
        this->_spinBoxRepairTime->setMinimum(1e-6);
        this->_spinBoxRepairTime->setMaximum(1e100);
        this->_spinBoxRepairTime->setDecimals(6);
        this->_spinBoxRepairTime->setSingleStep(0.01);
        this->_spinBoxRepairTime->setValue(1.0 / ((GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair());
        this->connect(this->_spinBoxRepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemRepairTime(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxRepairTime);
    }
}

void ParameterGOMarkovOperator::setItemFrequencyBreakdown(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyBreakdown(value);
}

void ParameterGOMarkovOperator::setItemFrequencyRepair(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyRepair(value);
    this->_spinBoxRepairTime->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemRepairTime(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyRepair(1.0 / value);
    this->_spinBoxFrequencyRepair->setValue(1.0 / value);
}
