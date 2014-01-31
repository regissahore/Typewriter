#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "ParameterGoMarkovOperator.h"
#include "ItemGoMarkovOperator.h"
#include "GoMarkovOperator.h"
#include "GoOperatorFactory.h"
#include "GoMarkovStatus.h"
#include "GoStatus.h"
#include "GoInput.h"
#include "GoOutput.h"
#include "MessageFactory.h"
#include "GoParameter.h"
#include "GoMarkovOperatorFactory.h"
#include "GoMarkovOperator9.h"
#include "GoMarkovOperator11.h"
#include "GoMarkovOperator12a.h"
#include "GoMarkovOperator13.h"
#include "GoMarkovOperator18.h"
#include "GoMarkovOperator18a.h"
#include "GoMarkovOperator19.h"
#include "GoMarkovOperator22.h"
#include "GoMarkovOperator23.h"
#include "DialogMatrixInput.h"

ParameterGoMarkovOperator::ParameterGoMarkovOperator(QWidget *parent) : ParameterGoOperator(parent)
{
}

void ParameterGoMarkovOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGoMarkovOperator *op = (ItemGoMarkovOperator*)item;
    switch (op->model()->type())
    {
    case GoMarkovOperatorFactory::Operator_Type_1:
        this->addMarkovBreakdownNumParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_2:
        break;
    case GoMarkovOperatorFactory::Operator_Type_5:
        this->addMarkovBreakdownNumParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_6:
        this->addMarkovBreakdownNumParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_9A1:
    case GoMarkovOperatorFactory::Operator_Type_9A2:
    case GoMarkovOperatorFactory::Operator_Type_9B1:
    case GoMarkovOperatorFactory::Operator_Type_9B2:
        this->addMarkovBreakdownNumParameter();
        this->addMarkov9FeedbackNumParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_10:
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_11:
        this->addMarkov11KParameter();
        this->addMarkov11IParameter();
        this->addMarkov11LParameter();
        this->addMarkov11JParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_12A:
        this->addMarkov12AUseDeltaParameter();
        this->addMarkov12ADeltaParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_13:
    case GoMarkovOperatorFactory::Operator_Type_13A:
    case GoMarkovOperatorFactory::Operator_Type_13B:
        this->addMarkov13RelationParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_15A:
        this->addMarkovBreakdownNumParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_15B:
        break;
    case GoMarkovOperatorFactory::Operator_Type_16:
        this->addMarkovShowOutput1Parameter();
        this->addMarkovShowOutput2Parameter();
        this->addMarkovBreakdownNumParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_17:
        this->addMarkovShowOutput1Parameter();
        this->addMarkovShowOutput2Parameter();
        this->addMarkovBreakdownNumParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_18:
        this->addMarkov18LambdaB1Parameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_18A:
        this->addMarkov18ABackupParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_19:
        this->addMarkovShowOutput1Parameter();
        this->addMarkovShowOutput2Parameter();
        this->addMarkovBreakdownNumParameter();
        this->addMarkov19DeltaNumParameter();
        this->addMarkov19DeltaParameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_20:
        break;
    case GoMarkovOperatorFactory::Operator_Type_22:
    case GoMarkovOperatorFactory::Operator_Type_22A:
    case GoMarkovOperatorFactory::Operator_Type_22B:
        this->addMarkovBreakdownNumParameter();
        this->addMarkov22Markov2Parameter();
        break;
    case GoMarkovOperatorFactory::Operator_Type_23:
        this->addMarkov23AlphaParameter();
        break;
    default:
        break;
    }
}

void ParameterGoMarkovOperator::addTypeParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Type"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(GoMarkovOperatorFactory::typeName(item->model()->type()), this));
    }
}

void ParameterGoMarkovOperator::addOperatorParameter()
{
    this->ParameterGoOperator::addOperatorParameter();
    if (this->_item != 0L)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Global Feedback"), this));
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->setChecked(((GoMarkovOperator*)item->model())->isGlobalFeedback());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovGlobalFeedback(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Show Parameter"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isDrawParameter());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovShowParameter(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGoMarkovOperator::setItemMarkovGlobalFeedback(bool value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    ((GoMarkovOperator*)item->model())->setIsGlobalFeedback(value);
    item->update();
}

void ParameterGoMarkovOperator::setItemMarkovShowParameter(bool value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    item->setIsDrawParameter(value);
    item->update();
}

void ParameterGoMarkovOperator::addMarkovBreakdownCorrelateParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator *model = (GoMarkovOperator*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Correlate"), this));
        this->_checkBoxBreakdownCorrelate = new QCheckBox(this);
        this->_checkBoxBreakdownCorrelate->setChecked(model->isBreakdownCorrelate());
        this->connect(this->_checkBoxBreakdownCorrelate, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovBreakdownCorrelate(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_checkBoxBreakdownCorrelate);
    }
}

void ParameterGoMarkovOperator::addMarkovBreakdownNumParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator *model = (GoMarkovOperator*)item->model();
        this->_markovBreakdownNumPos = this->_tableWidget->rowCount() + 1;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Status Number"), this));
        this->_spinBoxBreakdownNum = new QSpinBox(this);
        this->_spinBoxBreakdownNum->setMinimum(1);
        this->_spinBoxBreakdownNum->setMaximum(4);
        this->_spinBoxBreakdownNum->setValue(model->breakdownNum());
        this->connect(this->_spinBoxBreakdownNum, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkovBreakdownNum(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxBreakdownNum);
        switch (model->breakdownNum())
        {
        case 4:
            this->addMarkovStatus4Parameter();
        case 3:
            this->addMarkovStatus3Parameter();
        case 2:
            this->addMarkovStatus2Parameter();
        case 1:
            this->addMarkovStatus1Parameter();
        }
    }
}

void ParameterGoMarkovOperator::addMarkovStatus1Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator*)item->model())->markovStatus1();

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Time 1"), this));
        this->_spinBoxStatus1RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus1RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus1RepairTime->setMaximum(1e100);
        this->_spinBoxStatus1RepairTime->setDecimals(10);
        this->_spinBoxStatus1RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus1RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxStatus1RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkovRepairTime1()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus1RepairTime);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Rate 1"), this));
        this->_spinBoxStatus1FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus1FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus1FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus1FrequencyRepair->setDecimals(10);
        this->_spinBoxStatus1FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus1FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxStatus1FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkovFrequencyRepair1()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus1FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Failure Rate 1"), this));
        this->_spinBoxStatus1FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus1FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus1FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxStatus1FrequencyBreakdown->setDecimals(10);
        this->_spinBoxStatus1FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus1FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxStatus1FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown1(double)));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus1FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkovStatus2Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator*)item->model())->markovStatus2();

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Time 2"), this));
        this->_spinBoxStatus2RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus2RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus2RepairTime->setMaximum(1e100);
        this->_spinBoxStatus2RepairTime->setDecimals(10);
        this->_spinBoxStatus2RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus2RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxStatus2RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkovRepairTime2()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus2RepairTime);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Rate 2"), this));
        this->_spinBoxStatus2FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus2FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus2FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus2FrequencyRepair->setDecimals(10);
        this->_spinBoxStatus2FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus2FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxStatus2FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkovFrequencyRepair2()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus2FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Failure Rate 2"), this));
        this->_spinBoxStatus2FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus2FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus2FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxStatus2FrequencyBreakdown->setDecimals(10);
        this->_spinBoxStatus2FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus2FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxStatus2FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown2(double)));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus2FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkovStatus3Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator*)item->model())->markovStatus3();

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Time 3"), this));
        this->_spinBoxStatus3RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus3RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus3RepairTime->setMaximum(1e100);
        this->_spinBoxStatus3RepairTime->setDecimals(10);
        this->_spinBoxStatus3RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus3RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxStatus3RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkovRepairTime3()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus3RepairTime);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Rate 3"), this));
        this->_spinBoxStatus3FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus3FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus3FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus3FrequencyRepair->setDecimals(10);
        this->_spinBoxStatus3FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus3FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxStatus3FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkovFrequencyRepair3()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus3FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Failure Rate 3"), this));
        this->_spinBoxStatus3FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus3FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus3FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxStatus3FrequencyBreakdown->setDecimals(10);
        this->_spinBoxStatus3FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus3FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxStatus3FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown3(double)));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus3FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkovStatus4Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator*)item->model())->markovStatus4();

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Time 4"), this));
        this->_spinBoxStatus4RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus4RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus4RepairTime->setMaximum(1e100);
        this->_spinBoxStatus4RepairTime->setDecimals(10);
        this->_spinBoxStatus4RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus4RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxStatus4RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkovRepairTime4()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus4RepairTime);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Repair Rate 4"), this));
        this->_spinBoxStatus4FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus4FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus4FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus4FrequencyRepair->setDecimals(10);
        this->_spinBoxStatus4FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus4FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxStatus4FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkovFrequencyRepair4()));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus4FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovBreakdownNumPos);
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 0, new QLabel(tr("Failure Rate 4"), this));
        this->_spinBoxStatus4FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus4FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus4FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxStatus4FrequencyBreakdown->setDecimals(10);
        this->_spinBoxStatus4FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus4FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxStatus4FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown4(double)));
        this->_tableWidget->setCellWidget(this->_markovBreakdownNumPos, 1, this->_spinBoxStatus4FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::setItemMarkovBreakdownNum(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    for (int i = 0; i < model->breakdownNum() * 3; ++i)
    {
        this->_tableWidget->removeRow(this->_markovBreakdownNumPos);
    }
    model->setBreakdownNum(value);
    switch (model->breakdownNum())
    {
    case 4:
        this->addMarkovStatus4Parameter();
    case 3:
        this->addMarkovStatus3Parameter();
    case 2:
        this->addMarkovStatus2Parameter();
    case 1:
        this->addMarkovStatus1Parameter();
    }
}

void ParameterGoMarkovOperator::setItemMarkovBreakdownCorrelate(bool value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->setBreakdownCorrelate(value);
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyBreakdown1(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyRepair1()
{
    double value = this->_spinBoxStatus1FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyRepair(value);
    this->_spinBoxStatus1RepairTime->setValue((1.0 / model->markovStatus1()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovRepairTime1()
{
    double value = this->_spinBoxStatus1RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus1FrequencyRepair->setValue(model->markovStatus1()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyBreakdown2(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyRepair2()
{
    double value = this->_spinBoxStatus2FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyRepair(value);
    this->_spinBoxStatus2RepairTime->setValue(1.0 / model->markovStatus2()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovRepairTime2()
{
    double value = this->_spinBoxStatus2RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus2FrequencyRepair->setValue((model->markovStatus2()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyBreakdown3(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus3()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyRepair3()
{
    double value = this->_spinBoxStatus3FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus3()->setFrequencyRepair(value);
    this->_spinBoxStatus3RepairTime->setValue((1.0 / model->markovStatus3()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovRepairTime3()
{
    double value = this->_spinBoxStatus3RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus3()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus3FrequencyRepair->setValue(model->markovStatus3()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyBreakdown4(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus4()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkovFrequencyRepair4()
{
    double value = this->_spinBoxStatus4FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus4()->setFrequencyRepair(value);
    this->_spinBoxStatus4RepairTime->setValue((1.0 / model->markovStatus4()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkovRepairTime4()
{
    double value = this->_spinBoxStatus4RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator *model = (GoMarkovOperator*)item->model();
    model->markovStatus4()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus4FrequencyRepair->setValue(model->markovStatus4()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::addMarkov11KParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("K"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(1);
        spin->setMaximum(op->input()->number());
        spin->setValue(op->K());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11K(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::addMarkov11IParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("I"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->I());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11I(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::addMarkov11LParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("L"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->L());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11L(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::addMarkov11JParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("J"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->J());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11J(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::setItemMarkov11K(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();
    op->setK(value);
}

void ParameterGoMarkovOperator::setItemMarkov11I(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();
    op->setI(value);
}

void ParameterGoMarkovOperator::setItemMarkov11L(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();
    op->setL(value);
}

void ParameterGoMarkovOperator::setItemMarkov11J(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator11 *op = (GoMarkovOperator11*)item->model();
    op->setJ(value);
}

void ParameterGoMarkovOperator::addMarkov22Markov2Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator22 *op = (GoMarkovOperator22*)item->model();
        for (int i = op->lambda2()->size(); i < op->output()->number(); ++i)
        {
            op->lambda2()->push_back(0.0);
            op->mu2()->push_back(1.0);
        }
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Markov 2"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov22Markov2()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGoMarkovOperator::setItemMarkov22Markov2()
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator22 *op = (GoMarkovOperator22*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 22 Markov Status 2"));
    dialog->table()->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("lambda")));
    dialog->table()->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("mu")));
    dialog->table()->setRowCount(op->output()->number());
    dialog->table()->setColumnCount(2);
    for (int i = 0; i < op->output()->number(); ++i)
    {
        dialog->table()->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(op->lambda2()->at(i))));
        dialog->table()->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(op->mu2()->at(i))));
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->output()->number(); ++i)
        {
            (*op->lambda2())[i] = dialog->table()->item(i, 0)->text().toDouble();
            (*op->mu2())[i] = dialog->table()->item(i, 1)->text().toDouble();
        }
    }
    delete dialog;
}

void ParameterGoMarkovOperator::addMarkov23AlphaParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator23 *op = (GoMarkovOperator23*)item->model();
        for (int i = op->alpha()->size(); i < op->input()->number(); ++i)
        {
            op->alpha()->push_back(0.0);
        }
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Alpha"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov23Alpha()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGoMarkovOperator::setItemMarkov23Alpha()
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator23 *op = (GoMarkovOperator23*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 23 Alpha"));
    dialog->table()->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("alpha")));
    dialog->table()->setRowCount(op->input()->number());
    dialog->table()->setColumnCount(1);
    for (int i = 0; i < op->input()->number(); ++i)
    {
        dialog->table()->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(op->alpha()->at(i))));
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->input()->number(); ++i)
        {
            (*op->alpha())[i] = dialog->table()->item(i, 0)->text().toDouble();
        }
    }
    delete dialog;
}

void ParameterGoMarkovOperator::addMarkov13RelationParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator13 *op = (GoMarkovOperator13*)item->model();
        if (op->relation()->size() == 0)
        {
            op->initRelation();
        }
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Relation"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov13Relation()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGoMarkovOperator::setItemMarkov13Relation()
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator13 *op = (GoMarkovOperator13*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 13 Relation"));
    dialog->table()->setRowCount(op->input()->number());
    dialog->table()->setColumnCount(op->output()->number());
    for (int i = 0; i < op->input()->number(); ++i)
    {
        for (int j = 0; j < op->output()->number(); ++j)
        {
            dialog->table()->setItem(i, j, new QTableWidgetItem(QString("%1").arg(op->relation()->at(i).at(j))));
        }
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->input()->number(); ++i)
        {
            for (int j = 0; j < op->output()->number(); ++j)
            {
                (*op->relation())[i][j] = dialog->table()->item(i, j)->text().toDouble();
            }
        }
    }
    delete dialog;
}

void ParameterGoMarkovOperator::addMarkov18ABackupParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator18A *model = (GoMarkovOperator18A*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Backup Probability"), this));
        QDoubleSpinBox *spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1.0);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(model->backup());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov18ABackup(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::setItemMarkov18ABackup(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator18A *model = (GoMarkovOperator18A*)item->model();
    model->setBackup(value);
}

void ParameterGoMarkovOperator::addMarkov19DeltaNumParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator19 *model = (GoMarkovOperator19*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Delta Number"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(1);
        spin->setMaximum(0x7fffffff);
        spin->setValue(model->deltaNum());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov19DeltaNum(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::setItemMarkov19DeltaNum(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator19 *op = (GoMarkovOperator19*)item->model();
    op->setDeltaNum(value);
    for (int i = op->delta()->size(); i < op->deltaNum(); ++i)
    {
        op->ids()->push_back("0");
        op->delta()->push_back(0.0);
    }
}

void ParameterGoMarkovOperator::addMarkov19DeltaParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator19 *op = (GoMarkovOperator19*)item->model();
        for (int i = op->ids()->size(); i < op->deltaNum(); ++i)
        {
            op->ids()->push_back("0");
            op->delta()->push_back(1.0);
        }
        while (op->deltaNum() < op->ids()->size())
        {
            op->ids()->pop_back();
            op->delta()->pop_back();
        }
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Delta"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov19Delta()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGoMarkovOperator::setItemMarkov19Delta()
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator19 *op = (GoMarkovOperator19*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 19 Delta"));
    dialog->table()->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Relevent Operator ID")));
    dialog->table()->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("delta")));
    dialog->table()->setRowCount(op->deltaNum());
    dialog->table()->setColumnCount(2);
    for (int i = 0; i < op->deltaNum(); ++i)
    {
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setAlignment(Qt::AlignHCenter);
        lineEdit->setText(op->ids()->at(i));
        dialog->table()->setCellWidget(i, 0, lineEdit);
        dialog->table()->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(op->delta()->at(i))));
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->deltaNum(); ++i)
        {
            (*op->ids())[i] = ((QLineEdit*)dialog->table()->cellWidget(i, 0))->text();
            (*op->delta())[i] = dialog->table()->item(i, 1)->text().toDouble();
        }
    }
    delete dialog;
}

void ParameterGoMarkovOperator::addMarkov18LambdaB1Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator18 *model = (GoMarkovOperator18*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Lambda b1"), this));
        QDoubleSpinBox *spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1.0);
        spin->setDecimals(10);
        spin->setSingleStep(0.01);
        spin->setValue(model->lambdaB1().getValue(0));
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov18LambdaB1(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGoMarkovOperator::setItemMarkov18LambdaB1(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator18 *model = (GoMarkovOperator18*)item->model();
    model->setLambdaB1(value);
}

void ParameterGoMarkovOperator::addMarkovShowOutput1Parameter()
{
    if (0L != this->_item)
    {
        ItemGoOperator *item = (ItemGoOperator*)this->_item;
        QCheckBox *checkBox;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Show R1"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isShowOutput()->at(0));
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovShowOutput1(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGoMarkovOperator::addMarkovShowOutput2Parameter()
{
    if (0L != this->_item)
    {
        ItemGoOperator *item = (ItemGoOperator*)this->_item;
        QCheckBox *checkBox;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Show R2"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isShowOutput()->at(1));
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovShowOutput2(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGoMarkovOperator::setItemMarkovShowOutput1(bool value)
{
    ItemGoOperator *item = (ItemGoOperator*)this->_item;
    (*item->isShowOutput())[0] = value;
    item->update();
}

void ParameterGoMarkovOperator::setItemMarkovShowOutput2(bool value)
{
    ItemGoOperator *item = (ItemGoOperator*)this->_item;
    (*item->isShowOutput())[1] = value;
    item->update();
}

void ParameterGoMarkovOperator::addMarkov12AUseDeltaParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator12A *op = (GoMarkovOperator12A*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Use Delta"), this));
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->setChecked(op->isUseDelta());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemMarkov12AUseDelta(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGoMarkovOperator::addMarkov12ADeltaParameter()
{
    if (0L != this->_item)
    {
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Delta"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov12ADelta()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGoMarkovOperator::setItemMarkov12AUseDelta(bool value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator12A *op = (GoMarkovOperator12A*)item->model();
    op->setIsUseDelta(value);
}

void ParameterGoMarkovOperator::setItemMarkov12ADelta()
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator12A *op = (GoMarkovOperator12A*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 12A Delta"));
    dialog->table()->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Relevent Operator ID")));
    dialog->table()->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("delta")));
    dialog->table()->setRowCount(op->deltaNum());
    dialog->table()->setColumnCount(2);
    for (int i = 0; i < op->deltaNum(); ++i)
    {
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setAlignment(Qt::AlignHCenter);
        lineEdit->setText(op->ids()->at(i));
        dialog->table()->setCellWidget(i, 0, lineEdit);
        dialog->table()->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(op->delta()->at(i))));
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->deltaNum(); ++i)
        {
            (*op->ids())[i] = ((QLineEdit*)dialog->table()->cellWidget(i, 0))->text();
            (*op->delta())[i] = dialog->table()->item(i, 1)->text().toDouble();
        }
    }
    delete dialog;
}

void ParameterGoMarkovOperator::addMarkov9FeedbackNumParameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
        this->_markovFeedbackNumPos = this->_tableWidget->rowCount() + 1;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Feedback Status Number"), this));
        this->_spinBoxFeedbackNum = new QSpinBox(this);
        this->_spinBoxFeedbackNum->setMinimum(1);
        this->_spinBoxFeedbackNum->setMaximum(4);
        this->_spinBoxFeedbackNum->setValue(model->feedbackNum());
        this->connect(this->_spinBoxFeedbackNum, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov9FeedbackNum(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxFeedbackNum);
        switch (model->feedbackNum())
        {
        case 4:
            this->addMarkov9Feedback4Parameter();
        case 3:
            this->addMarkov9Feedback3Parameter();
        case 2:
            this->addMarkov9Feedback2Parameter();
        case 1:
            this->addMarkov9Feedback1Parameter();
        }
    }
}

void ParameterGoMarkovOperator::addMarkov9Feedback1Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator9*)item->model())->feedbackStatus1();

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Time 1"), this));
        this->_spinBoxFeedback1RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxFeedback1RepairTime->setMinimum(1e-6);
        this->_spinBoxFeedback1RepairTime->setMaximum(1e100);
        this->_spinBoxFeedback1RepairTime->setDecimals(10);
        this->_spinBoxFeedback1RepairTime->setSingleStep(0.01);
        this->_spinBoxFeedback1RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxFeedback1RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9RepairTime1()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback1RepairTime);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Rate 1"), this));
        this->_spinBoxFeedback1FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFeedback1FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFeedback1FrequencyRepair->setMaximum(1e100);
        this->_spinBoxFeedback1FrequencyRepair->setDecimals(10);
        this->_spinBoxFeedback1FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFeedback1FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxFeedback1FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9FrequencyRepair1()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback1FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Failure Rate 1"), this));
        this->_spinBoxFeedback1FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFeedback1FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFeedback1FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxFeedback1FrequencyBreakdown->setDecimals(10);
        this->_spinBoxFeedback1FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFeedback1FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxFeedback1FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FrequencyBreakdown1(double)));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback1FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkov9Feedback2Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator9*)item->model())->feedbackStatus2();

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Time 2"), this));
        this->_spinBoxFeedback2RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxFeedback2RepairTime->setMinimum(1e-6);
        this->_spinBoxFeedback2RepairTime->setMaximum(1e100);
        this->_spinBoxFeedback2RepairTime->setDecimals(10);
        this->_spinBoxFeedback2RepairTime->setSingleStep(0.01);
        this->_spinBoxFeedback2RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxFeedback2RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9RepairTime2()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback2RepairTime);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Rate 2"), this));
        this->_spinBoxFeedback2FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFeedback2FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFeedback2FrequencyRepair->setMaximum(1e100);
        this->_spinBoxFeedback2FrequencyRepair->setDecimals(10);
        this->_spinBoxFeedback2FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFeedback2FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxFeedback2FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9FrequencyRepair2()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback2FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Failure Rate 2"), this));
        this->_spinBoxFeedback2FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFeedback2FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFeedback2FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxFeedback2FrequencyBreakdown->setDecimals(10);
        this->_spinBoxFeedback2FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFeedback2FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxFeedback2FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FrequencyBreakdown2(double)));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback2FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkov9Feedback3Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator9*)item->model())->feedbackStatus3();

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Time 3"), this));
        this->_spinBoxFeedback3RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxFeedback3RepairTime->setMinimum(1e-6);
        this->_spinBoxFeedback3RepairTime->setMaximum(1e100);
        this->_spinBoxFeedback3RepairTime->setDecimals(10);
        this->_spinBoxFeedback3RepairTime->setSingleStep(0.01);
        this->_spinBoxFeedback3RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxFeedback3RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9RepairTime3()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback3RepairTime);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Rate 3"), this));
        this->_spinBoxFeedback3FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFeedback3FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFeedback3FrequencyRepair->setMaximum(1e100);
        this->_spinBoxFeedback3FrequencyRepair->setDecimals(10);
        this->_spinBoxFeedback3FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFeedback3FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxFeedback3FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9FrequencyRepair3()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback3FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Failure Rate 3"), this));
        this->_spinBoxFeedback3FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFeedback3FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFeedback3FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxFeedback3FrequencyBreakdown->setDecimals(10);
        this->_spinBoxFeedback3FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFeedback3FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxFeedback3FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FrequencyBreakdown3(double)));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback3FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::addMarkov9Feedback4Parameter()
{
    if (0L != this->_item)
    {
        ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
        GoMarkovStatus *status = ((GoMarkovOperator9*)item->model())->feedbackStatus4();

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Time 4"), this));
        this->_spinBoxFeedback4RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxFeedback4RepairTime->setMinimum(1e-6);
        this->_spinBoxFeedback4RepairTime->setMaximum(1e100);
        this->_spinBoxFeedback4RepairTime->setDecimals(10);
        this->_spinBoxFeedback4RepairTime->setSingleStep(0.01);
        this->_spinBoxFeedback4RepairTime->setValue((1.0 / status->frequencyRepair()).getValue(0));
        this->connect(this->_spinBoxFeedback4RepairTime, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9RepairTime4()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback4RepairTime);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Repair Rate 4"), this));
        this->_spinBoxFeedback4FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFeedback4FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFeedback4FrequencyRepair->setMaximum(1e100);
        this->_spinBoxFeedback4FrequencyRepair->setDecimals(10);
        this->_spinBoxFeedback4FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFeedback4FrequencyRepair->setValue(status->frequencyRepair().getValue(0));
        this->connect(this->_spinBoxFeedback4FrequencyRepair, SIGNAL(editingFinished()), this, SLOT(setItemMarkov9FrequencyRepair4()));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback4FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovFeedbackNumPos);
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 0, new QLabel(tr("Feedback Failure Rate 4"), this));
        this->_spinBoxFeedback4FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFeedback4FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFeedback4FrequencyBreakdown->setMaximum(1.0);
        this->_spinBoxFeedback4FrequencyBreakdown->setDecimals(10);
        this->_spinBoxFeedback4FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFeedback4FrequencyBreakdown->setValue(status->frequencyBreakdown().getValue(0));
        this->connect(this->_spinBoxFeedback4FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FrequencyBreakdown4(double)));
        this->_tableWidget->setCellWidget(this->_markovFeedbackNumPos, 1, this->_spinBoxFeedback4FrequencyBreakdown);
    }
}

void ParameterGoMarkovOperator::setItemMarkov9FeedbackNum(int value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    for (int i = 0; i < model->feedbackNum() * 3; ++i)
    {
        this->_tableWidget->removeRow(this->_markovFeedbackNumPos);
    }
    model->setFeedbackNum(value);
    switch (model->feedbackNum())
    {
    case 4:
        this->addMarkov9Feedback4Parameter();
    case 3:
        this->addMarkov9Feedback3Parameter();
    case 2:
        this->addMarkov9Feedback2Parameter();
    case 1:
        this->addMarkov9Feedback1Parameter();
    }
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyBreakdown1(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus1()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyRepair1()
{
    double value = this->_spinBoxFeedback1FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus1()->setFrequencyRepair(value);
    this->_spinBoxFeedback1RepairTime->setValue((1.0 / model->feedbackStatus1()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9RepairTime1()
{
    double value = this->_spinBoxFeedback1RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus1()->setFrequencyRepair(1.0 / value);
    this->_spinBoxFeedback1FrequencyRepair->setValue(model->feedbackStatus1()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyBreakdown2(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus2()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyRepair2()
{
    double value = this->_spinBoxFeedback2FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus2()->setFrequencyRepair(value);
    this->_spinBoxFeedback2RepairTime->setValue(1.0 / model->feedbackStatus2()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9RepairTime2()
{
    double value = this->_spinBoxFeedback2RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus2()->setFrequencyRepair(1.0 / value);
    this->_spinBoxFeedback2FrequencyRepair->setValue((model->feedbackStatus2()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyBreakdown3(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus3()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyRepair3()
{
    double value = this->_spinBoxFeedback3FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus3()->setFrequencyRepair(value);
    this->_spinBoxFeedback3RepairTime->setValue((1.0 / model->feedbackStatus3()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9RepairTime3()
{
    double value = this->_spinBoxFeedback3RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus3()->setFrequencyRepair(1.0 / value);
    this->_spinBoxFeedback3FrequencyRepair->setValue(model->feedbackStatus3()->frequencyRepair().getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyBreakdown4(double value)
{
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus4()->setFrequencyBreakdown(value);
}

void ParameterGoMarkovOperator::setItemMarkov9FrequencyRepair4()
{
    double value = this->_spinBoxFeedback4FrequencyRepair->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus4()->setFrequencyRepair(value);
    this->_spinBoxFeedback4RepairTime->setValue((1.0 / model->feedbackStatus4()->frequencyRepair()).getValue(0));
}

void ParameterGoMarkovOperator::setItemMarkov9RepairTime4()
{
    double value = this->_spinBoxFeedback4RepairTime->value();
    ItemGoMarkovOperator *item = (ItemGoMarkovOperator*)this->_item;
    GoMarkovOperator9 *model = (GoMarkovOperator9*)item->model();
    model->feedbackStatus4()->setFrequencyRepair(1.0 / value);
    this->_spinBoxFeedback4FrequencyRepair->setValue(model->feedbackStatus4()->frequencyRepair().getValue(0));
}
