#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "parametergomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "gooperatorfactory.h"
#include "gomarkovstatus.h"
#include "gostatus.h"
#include "goinput.h"
#include "gooutput.h"
#include "messagefactory.h"
#include "goparameter.h"
#include "gomarkovoperatorfactory.h"
#include "gomarkovoperator9a.h"
#include "gomarkovoperator11.h"
#include "gomarkovoperator13.h"
#include "gomarkovoperator18.h"
#include "gomarkovoperator18a.h"
#include "gomarkovoperator19.h"
#include "gomarkovoperator22.h"
#include "gomarkovoperator23.h"
#include "dialogmatrixinput.h"

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
        this->addMarkovDualBreakdownParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_2:
        break;
    case GOMarkovOperatorFactory::Operator_Type_5:
        this->addMarkovDualBreakdownParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_6:
        this->addMarkovDualBreakdownParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_9A1:
        this->addMarkovBreakdownCorrelateParameter();
    case GOMarkovOperatorFactory::Operator_Type_9A2:
        this->addMarkovDualBreakdownParameter();
        this->addMarkov9FeedbackParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_11:
        this->addMarkov11KParameter();
        this->addMarkov11IParameter();
        this->addMarkov11LParameter();
        this->addMarkov11JParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_12A:
        break;
    case GOMarkovOperatorFactory::Operator_Type_13:
    case GOMarkovOperatorFactory::Operator_Type_13A:
    case GOMarkovOperatorFactory::Operator_Type_13B:
        this->addMarkov13RelationParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_15A:
        this->addMarkovDualBreakdownParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_15B:
        break;
    case GOMarkovOperatorFactory::Operator_Type_16:
        this->addMarkovDualBreakdownParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_17:
        this->addMarkovDualBreakdownParameter();
        this->addMarkovBreakdownCorrelateParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_18:
        this->addMarkov18LambdaB1Parameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_18A:
        this->addMarkov18ABackupParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_19:
        this->addMarkovDualBreakdownParameter();
        this->addMarkov19DeltaNumParameter();
        this->addMarkov19DeltaParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_20:
        break;
    case GOMarkovOperatorFactory::Operator_Type_22:
    case GOMarkovOperatorFactory::Operator_Type_22A:
    case GOMarkovOperatorFactory::Operator_Type_22B:
        this->addMarkovDualBreakdownParameter();
        this->addMarkov22Markov2Parameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_23:
        this->addMarkov23AlphaParameter();
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

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Time"), this));
        this->_spinBoxRepairTime = new QDoubleSpinBox(this);
        this->_spinBoxRepairTime->setMinimum(1e-6);
        this->_spinBoxRepairTime->setMaximum(1e100);
        this->_spinBoxRepairTime->setDecimals(12);
        this->_spinBoxRepairTime->setSingleStep(0.01);
        this->_spinBoxRepairTime->setValue(1.0 / status->frequencyRepair());
        this->connect(this->_spinBoxRepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemRepairTime(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxRepairTime);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Rate"), this));
        this->_spinBoxFrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyRepair->setMinimum(1e-6);
        this->_spinBoxFrequencyRepair->setMaximum(1e100);
        this->_spinBoxFrequencyRepair->setDecimals(12);
        this->_spinBoxFrequencyRepair->setSingleStep(0.01);
        this->_spinBoxFrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBoxFrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyRepair(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxFrequencyRepair);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Failure Rate"), this));
        this->_spinBoxFrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxFrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxFrequencyBreakdown->setMaximum(1e100);
        this->_spinBoxFrequencyBreakdown->setDecimals(12);
        this->_spinBoxFrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxFrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBoxFrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemFrequencyBreakdown(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxFrequencyBreakdown);
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

void ParameterGOMarkovOperator::addMarkovDualBreakdownParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator *model = (GOMarkovOperator*)item->model();
        this->_markovDualBreakdownPos = this->_tableWidget->rowCount();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Dual Breakdown"), this));
        this->_checkBoxDualBreakdown = new QCheckBox(this);
        this->_checkBoxDualBreakdown->setChecked(model->isDualBreakdown());
        this->connect(this->_checkBoxDualBreakdown, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovDualBreakdown(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_checkBoxDualBreakdown);
        if (model->isDualBreakdown())
        {
            this->addMarkovStatus2Parameter();
            this->addMarkovStatus1Parameter();
        }
        else
        {
            this->addMarkovParameter();
        }
    }
}

void ParameterGOMarkovOperator::addMarkovBreakdownCorrelateParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator *model = (GOMarkovOperator*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Breakdown Correlate"), this));
        this->_checkBoxBreakdownCorrelate = new QCheckBox(this);
        this->_checkBoxBreakdownCorrelate->setChecked(model->isBreakdownCorrelate());
        this->connect(this->_checkBoxBreakdownCorrelate, SIGNAL(toggled(bool)), this, SLOT(setItemMarkovBreakdownCorrelate(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_checkBoxBreakdownCorrelate);
    }
}

void ParameterGOMarkovOperator::addMarkovStatus1Parameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovStatus *status = ((GOMarkovOperator*)item->model())->markovStatus1();

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Time 1"), this));
        this->_spinBoxStatus1RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus1RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus1RepairTime->setMaximum(1e100);
        this->_spinBoxStatus1RepairTime->setDecimals(12);
        this->_spinBoxStatus1RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus1RepairTime->setValue(1.0 / status->frequencyRepair());
        this->connect(this->_spinBoxStatus1RepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovRepairTime1(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus1RepairTime);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Rate 1"), this));
        this->_spinBoxStatus1FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus1FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus1FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus1FrequencyRepair->setDecimals(12);
        this->_spinBoxStatus1FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus1FrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBoxStatus1FrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyRepair1(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus1FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Failure Rate 1"), this));
        this->_spinBoxStatus1FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus1FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus1FrequencyBreakdown->setMaximum(1e100);
        this->_spinBoxStatus1FrequencyBreakdown->setDecimals(12);
        this->_spinBoxStatus1FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus1FrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBoxStatus1FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown1(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus1FrequencyBreakdown);
    }
}

void ParameterGOMarkovOperator::addMarkovStatus2Parameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovStatus *status = ((GOMarkovOperator*)item->model())->markovStatus2();

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Time 2"), this));
        this->_spinBoxStatus2RepairTime = new QDoubleSpinBox(this);
        this->_spinBoxStatus2RepairTime->setMinimum(1e-6);
        this->_spinBoxStatus2RepairTime->setMaximum(1e100);
        this->_spinBoxStatus2RepairTime->setDecimals(12);
        this->_spinBoxStatus2RepairTime->setSingleStep(0.01);
        this->_spinBoxStatus2RepairTime->setValue(1.0 / status->frequencyRepair());
        this->connect(this->_spinBoxStatus2RepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovRepairTime2(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus2RepairTime);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Repair Rate 2"), this));
        this->_spinBoxStatus2FrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBoxStatus2FrequencyRepair->setMinimum(1e-6);
        this->_spinBoxStatus2FrequencyRepair->setMaximum(1e100);
        this->_spinBoxStatus2FrequencyRepair->setDecimals(12);
        this->_spinBoxStatus2FrequencyRepair->setSingleStep(0.01);
        this->_spinBoxStatus2FrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBoxStatus2FrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyRepair2(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus2FrequencyRepair);

        this->_tableWidget->insertRow(this->_markovDualBreakdownPos);
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 0, new QLabel(tr("Failure Rate 2"), this));
        this->_spinBoxStatus2FrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBoxStatus2FrequencyBreakdown->setMinimum(0.0);
        this->_spinBoxStatus2FrequencyBreakdown->setMaximum(1e100);
        this->_spinBoxStatus2FrequencyBreakdown->setDecimals(12);
        this->_spinBoxStatus2FrequencyBreakdown->setSingleStep(0.01);
        this->_spinBoxStatus2FrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBoxStatus2FrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkovFrequencyBreakdown2(double)));
        this->_tableWidget->setCellWidget(this->_markovDualBreakdownPos, 1, this->_spinBoxStatus2FrequencyBreakdown);
    }
}

void ParameterGOMarkovOperator::setItemMarkovDualBreakdown(bool value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->setDualBreakdown(value);
    if (value)
    {
        for (int i = 0; i < 3; ++i)
        {
            this->_tableWidget->removeRow(this->_markovDualBreakdownPos);
        }
        this->addMarkovStatus2Parameter();
        this->addMarkovStatus1Parameter();
    }
    else
    {
        for (int i = 0; i < 6; ++i)
        {
            this->_tableWidget->removeRow(this->_markovDualBreakdownPos);
        }
        this->addMarkovParameter();
    }
}

void ParameterGOMarkovOperator::setItemMarkovBreakdownCorrelate(bool value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->setBreakdownCorrelate(value);
}

void ParameterGOMarkovOperator::setItemMarkovFrequencyBreakdown1(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyBreakdown(value);
}

void ParameterGOMarkovOperator::setItemMarkovFrequencyRepair1(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyRepair(value);
    this->_spinBoxStatus1RepairTime->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemMarkovRepairTime1(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus1()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus1FrequencyRepair->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemMarkovFrequencyBreakdown2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyBreakdown(value);
}

void ParameterGOMarkovOperator::setItemMarkovFrequencyRepair2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyRepair(value);
    this->_spinBoxStatus2RepairTime->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemMarkovRepairTime2(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator *model = (GOMarkovOperator*)item->model();
    model->markovStatus2()->setFrequencyRepair(1.0 / value);
    this->_spinBoxStatus2FrequencyRepair->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::addMarkov11KParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();

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

void ParameterGOMarkovOperator::addMarkov11IParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("I"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->I());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11I(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovOperator::addMarkov11LParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("L"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->L());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11L(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovOperator::addMarkov11JParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("J"), this));
        QSpinBox *spin = new QSpinBox(this);
        spin->setMinimum(0);
        spin->setValue(op->J());
        this->connect(spin, SIGNAL(valueChanged(int)), this, SLOT(setItemMarkov11J(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovOperator::setItemMarkov11K(int value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();
    op->setK(value);
}

void ParameterGOMarkovOperator::setItemMarkov11I(int value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();
    op->setI(value);
}

void ParameterGOMarkovOperator::setItemMarkov11L(int value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();
    op->setL(value);
}

void ParameterGOMarkovOperator::setItemMarkov11J(int value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator11 *op = (GOMarkovOperator11*)item->model();
    op->setJ(value);
}

void ParameterGOMarkovOperator::addMarkov22Markov2Parameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator22 *op = (GOMarkovOperator22*)item->model();
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

void ParameterGOMarkovOperator::setItemMarkov22Markov2()
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator22 *op = (GOMarkovOperator22*)item->model();
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

void ParameterGOMarkovOperator::addMarkov23AlphaParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator23 *op = (GOMarkovOperator23*)item->model();
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

void ParameterGOMarkovOperator::setItemMarkov23Alpha()
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator23 *op = (GOMarkovOperator23*)item->model();
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

void ParameterGOMarkovOperator::addMarkov13RelationParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator13 *op = (GOMarkovOperator13*)item->model();
        op->initRelation();
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Relation"), this));
        QPushButton *button = new QPushButton(this);
        button->setText(tr("Click to Edit..."));
        this->connect(button, SIGNAL(clicked()), this, SLOT(setItemMarkov13Relation()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, button);
    }
}

void ParameterGOMarkovOperator::setItemMarkov13Relation()
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator13 *op = (GOMarkovOperator13*)item->model();
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

void ParameterGOMarkovOperator::addMarkov9FeedbackParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovStatus *status = ((GOMarkovOperator9A*)item->model())->markovFeedbackStatus();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Failure Rate Feedback"), this));
        this->_spinBox9FeedbackFrequencyBreakdown = new QDoubleSpinBox(this);
        this->_spinBox9FeedbackFrequencyBreakdown->setMinimum(0.0);
        this->_spinBox9FeedbackFrequencyBreakdown->setMaximum(1e100);
        this->_spinBox9FeedbackFrequencyBreakdown->setDecimals(12);
        this->_spinBox9FeedbackFrequencyBreakdown->setSingleStep(0.01);
        this->_spinBox9FeedbackFrequencyBreakdown->setValue(status->frequencyBreakdown());
        this->connect(this->_spinBox9FeedbackFrequencyBreakdown, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FeedbackFrequencyBreakdown(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox9FeedbackFrequencyBreakdown);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Rate Feedback"), this));
        this->_spinBox9FeedbackFrequencyRepair = new QDoubleSpinBox(this);
        this->_spinBox9FeedbackFrequencyRepair->setMinimum(1e-6);
        this->_spinBox9FeedbackFrequencyRepair->setMaximum(1e100);
        this->_spinBox9FeedbackFrequencyRepair->setDecimals(12);
        this->_spinBox9FeedbackFrequencyRepair->setSingleStep(0.01);
        this->_spinBox9FeedbackFrequencyRepair->setValue(status->frequencyRepair());
        this->connect(this->_spinBox9FeedbackFrequencyRepair, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FeedbackFrequencyRepair(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox9FeedbackFrequencyRepair);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Repair Time Feedback"), this));
        this->_spinBox9FeedbackRepairTime = new QDoubleSpinBox(this);
        this->_spinBox9FeedbackRepairTime->setMinimum(1e-6);
        this->_spinBox9FeedbackRepairTime->setMaximum(1e100);
        this->_spinBox9FeedbackRepairTime->setDecimals(12);
        this->_spinBox9FeedbackRepairTime->setSingleStep(0.01);
        this->_spinBox9FeedbackRepairTime->setValue(1.0 / status->frequencyRepair());
        this->connect(this->_spinBox9FeedbackRepairTime, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov9FeedbackRepairTime(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox9FeedbackRepairTime);
    }
}

void ParameterGOMarkovOperator::setItemMarkov9FeedbackFrequencyBreakdown(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator9A *model = (GOMarkovOperator9A*)item->model();
    model->markovFeedbackStatus()->setFrequencyBreakdown(value);
}

void ParameterGOMarkovOperator::setItemMarkov9FeedbackFrequencyRepair(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator9A *model = (GOMarkovOperator9A*)item->model();
    model->markovFeedbackStatus()->setFrequencyRepair(value);
    this->_spinBox9FeedbackRepairTime->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::setItemMarkov9FeedbackRepairTime(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator9A *model = (GOMarkovOperator9A*)item->model();
    model->markovFeedbackStatus()->setRepairTime(1.0 / value);
    this->_spinBox9FeedbackFrequencyRepair->setValue(1.0 / value);
}

void ParameterGOMarkovOperator::addMarkov18ABackupParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator18A *model = (GOMarkovOperator18A*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Backup Probability"), this));
        QDoubleSpinBox *spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1.0);
        spin->setDecimals(12);
        spin->setSingleStep(0.01);
        spin->setValue(model->backup());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov18ABackup(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovOperator::setItemMarkov18ABackup(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator18A *model = (GOMarkovOperator18A*)item->model();
    model->setBackup(value);
}

void ParameterGOMarkovOperator::addMarkov19DeltaNumParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator19 *model = (GOMarkovOperator19*)item->model();

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

void ParameterGOMarkovOperator::setItemMarkov19DeltaNum(int value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator19 *op = (GOMarkovOperator19*)item->model();
    op->setDeltaNum(value);
}

void ParameterGOMarkovOperator::addMarkov19DeltaParameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator19 *op = (GOMarkovOperator19*)item->model();
        for (int i = op->a()->size(); i < op->deltaNum(); ++i)
        {
            op->a()->push_back(1);
            op->delta()->push_back(1.0);
        }
        while (op->deltaNum() < op->a()->size())
        {
            op->a()->pop_back();
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

void ParameterGOMarkovOperator::setItemMarkov19Delta()
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator19 *op = (GOMarkovOperator19*)item->model();
    DialogMatrixInput *dialog = new DialogMatrixInput(this);
    dialog->setWindowTitle(tr("Operator 19 Delta"));
    dialog->table()->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("i")));
    dialog->table()->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("delta")));
    dialog->table()->setRowCount(op->deltaNum());
    dialog->table()->setColumnCount(2);
    for (int i = 0; i < op->deltaNum(); ++i)
    {
        dialog->table()->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(op->a()->at(i))));
        dialog->table()->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(op->delta()->at(i))));
    }
    if (dialog->exec() == QDialog::Accepted)
    {
        for (int i = 0; i < op->deltaNum(); ++i)
        {
            (*op->a())[i] = dialog->table()->item(i, 0)->text().toInt();
            (*op->delta())[i] = dialog->table()->item(i, 1)->text().toDouble();
        }
    }
    delete dialog;
}

void ParameterGOMarkovOperator::addMarkov18LambdaB1Parameter()
{
    if (0L != this->_item)
    {
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
        GOMarkovOperator18 *model = (GOMarkovOperator18*)item->model();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Lambda b1"), this));
        QDoubleSpinBox *spin = new QDoubleSpinBox(this);
        spin->setMinimum(0.0);
        spin->setMaximum(1.0);
        spin->setDecimals(12);
        spin->setSingleStep(0.01);
        spin->setValue(model->lambdaB1());
        this->connect(spin, SIGNAL(valueChanged(double)), this, SLOT(setItemMarkov18LambdaB1(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, spin);
    }
}

void ParameterGOMarkovOperator::setItemMarkov18LambdaB1(double value)
{
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    GOMarkovOperator18 *model = (GOMarkovOperator18*)item->model();
    model->setLambdaB1(value);
}
