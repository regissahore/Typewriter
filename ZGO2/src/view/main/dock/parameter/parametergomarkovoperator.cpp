#include <QLabel>
#include <QCheckBox>
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
#include "dialog13ainput.h"
#include "gomarkovoperator1.h"

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
        this->addMarkov1DualBreakdownParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_2:
        break;
    case GOMarkovOperatorFactory::Operator_Type_5:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_6:
        this->addMarkovParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_16:
        this->addMarkovParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_17:
        this->addMarkovParameter();
        this->addMarkovBreakdownCorrelateParameter();
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
        GOMarkovStatus *status = ((GOMarkovOperator*)item->model())->markovStatus();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Failure Rate"), this));
        this->_spinBoxFrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFrequencyBreakdown->setMaximum(1e100);
        this->_spinBoxFrequencyBreakdown->setDecimals(6);
        this->_spinBoxFrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBoxFrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyBreakdown(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxFrequencyBreakdown);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Rate"), this));
        this->_spinBoxFrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFrequencyRepair->setMaximum(1e100);
        this->_spinBoxFrequencyRepair->setDecimals(6);
        this->_spinBoxFrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBoxFrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyRepair(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxFrequencyRepair);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Time"), this));
        this->_spinBoxRepairTime = new QDoubleSpinBox(this);
        this->_spinBoxRepairTime->setMinimum(1e-6);
        this->_spinBoxRepairTime->setMaximum(1e100);
        this->_spinBoxRepairTime->setDecimals(6);
        this->_spinBoxRepairTime->setSingleStep(0.01);
        this->_spinBoxRepairTime->setValue(1.0 / status->frequencyRepair());
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

void ParameterGOMarkovOperator::addMarkov1DualBreakdownParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();
        this->_markov1DualBreakdownPos = this->_tableWidget->rowCount();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Dual Breakdown"), this));
        this->_checkBox1DualBreakdown = new QCheckBox(this);
        this->_checkBox1DualBreakdown->setChecked(model->isDualBreakdown());
        this->connect(this->_checkBox1DualBreakdown, SIGNAL(toggled(bool)), this, SLOT(setItemMarkov1DualBreakdown(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_checkBox1DualBreakdown);
        if (model->isDualBreakdown())
        {
            this->addMarkov1Status2Parameter();
        }
    }
}

void ParameterGOMarkovOperator::addMarkovBreakdownCorrelateParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Correlate"), this));
        this->_checkBoxBreakdownCorrelate = new QCheckBox(this);
        this->_checkBoxBreakdownCorrelate->setChecked(model->isBreakdownCorrelate());
        this->connect(this->_checkBoxBreakdownCorrelate, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovBreakdownCorrelate(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_checkBoxBreakdownCorrelate);
    }
}

void ParameterGOMarkovOperator::addMarkov1Status2Parameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovStatus *status = ((GOMarkovOperator1*)item->model())->markovStatus2();

        this->_tableWidget->insertRow(this->_markov1DualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 0, new QLabel(tr("Repair Time 2"), this));
        this->_spinBox1Status2RepairTime = new QDoubleSpinBox(this);
        this->_spinBox1Status2RepairTime->setMinimum(1e-6);
        this->_spinBox1Status2RepairTime->setMaximum(1e100);
        this->_spinBox1Status2RepairTime->setDecimals(6);
        this->_spinBox1Status2RepairTime->setSingleStep(0.01);
        this->_spinBox1Status2RepairTime->setValue(1.0 / status->frequencyRepair());
        this->connect(this->_spinBox1Status2RepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov1RepairTime2(double)));
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 1, this->_spinBox1Status2RepairTime);

        this->_tableWidget->insertRow(this->_markov1DualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 0, new QLabel(tr("Repair Rate 2"), this));
        this->_spinBox1Status2FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBox1Status2FrequencyRepair->setMinimum(1e-6);
        this->_spinBox1Status2FrequencyRepair->setMaximum(1e100);
        this->_spinBox1Status2FrequencyRepair->setDecimals(6);
        this->_spinBox1Status2FrequencyRepair->setSingleStep(0.01);
        this->_spinBox1Status2FrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBox1Status2FrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov1FrequencyRepair2(double)));
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 1, this->_spinBox1Status2FrequencyRepair);

        this->_tableWidget->insertRow(this->_markov1DualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 0, new QLabel(tr("Failure Rate 2"), this));
        this->_spinBox1Status2FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBox1Status2FrequencyBreakdown->setMinimum(0.0);
        this->_spinBox1Status2FrequencyBreakdown->setMaximum(1e100);
        this->_spinBox1Status2FrequencyBreakdown->setDecimals(6);
        this->_spinBox1Status2FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBox1Status2FrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBox1Status2FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov1FrequencyBreakdown2(double)));
        this->_tableWidget->setCellWidget(this->_markov1DualBreakdownPos, 1, this->_spinBox1Status2FrequencyBreakdown);
    }
}

void ParameterGOMarkovOperator::setItemMarkov1DualBreakdown(bool value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();
    model->setDualBreakdown(value);
    if (value)
    {
        this->addMarkov1Status2Parameter();
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            this->_tableWidget->removeRow(this->_markov1DualBreakdownPos);
        }
    }
}

void ParameterGOMarkovOperator::setItemMarkovBreakdownCorrelate(bool value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->setBreakdownCorrelate(value);
}

void ParameterGOMarkovOperator::setItemMarkov1FrequencyBreakdown2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();
    model->markovStatus2()->setFrequencyBreakdown(value);
}

void ParameterGOMarkovOperator::setItemMarkov1FrequencyRepair2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();
    model->markovStatus2()->setFrequencyRepair(value);
    this->_spinBox1Status2RepairTime->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemMarkov1RepairTime2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator1 *model = (GOMarkovOperator1*)item->model();
    model->markovStatus2()->setRepairTime(1.0 / value);
    this->_spinBox1Status2FrequencyRepair->setValue(1.0 / value);
}
