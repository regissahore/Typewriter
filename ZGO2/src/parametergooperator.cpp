#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "parametergooperator.h"
#include "itemgooperator.h"
#include "gooperator.h"
#include "gostatus.h"
#include "gooperatorfactory.h"
#include "dialoggoprobability.h"
#include "goparameter.h"
#include "messagefactory.h"
#include "goinput.h"

ParameterGOOperator::ParameterGOOperator(QWidget *parent) : ParameterAbstract(parent)
{
    this->_spinBoxProbability0 = 0L;
}

void ParameterGOOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGOOperator *op = (ItemGOOperator*)item;
    switch (op->model()->type())
    {
    case GOOperatorFactory::Operator_Type_1:
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_2:
        break;
    case GOOperatorFactory::Operator_Type_3:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_5:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_6:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_7:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_9:
        this->addOperator9XYParameter();
        break;
    case GOOperatorFactory::Operator_Type_10:
        break;
    case GOOperatorFactory::Operator_Type_11:
        this->addOperator11KParameter();
        break;
    default:
        break;
    }
}

void ParameterGOOperator::addIDParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("ID"), this));
        this->_spinBoxID = new QSpinBox(this);
        this->_spinBoxID->setMinimum(1);
        this->_spinBoxID->setMaximum(0x7fffffff);
        this->_spinBoxID->setValue(item->model()->id());
        this->connect(this->_spinBoxID, SIGNAL(valueChanged(int)), this, SLOT(setItemID(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxID);
    }
}

void ParameterGOOperator::addTypeParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Type"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(QString("%1").arg(item->model()->type()), this));
    }
}

void ParameterGOOperator::addOperatorParameter()
{
    if (0L != this->_item)
    {
        this->addFlipParameter();
        this->addIDParameter();
        this->addTypeParameter();
    }
}

void ParameterGOOperator::setItemID(int value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->setId(value);
    item->update();
}

void ParameterGOOperator::addFlipParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        QCheckBox *checkBox;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Horizon Flip"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isHorizonFlip());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemHorizonFlip(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Vertical Flip"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isVerticalFlip());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setItemVerticalFlip(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGOOperator::setItemHorizonFlip(bool value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->setIsHorizonFlip(value);
    item->horizonFlip();
}

void ParameterGOOperator::setItemVerticalFlip(bool value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->setIsVerticalFlip(value);
    item->verticalFlip();
}

void ParameterGOOperator::addProbability0Parameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Probability 0"), this));
        this->_spinBoxProbability0 = new QDoubleSpinBox(this);
        this->_spinBoxProbability0->setMinimum(0.0);
        this->_spinBoxProbability0->setMaximum(1.0);
        this->_spinBoxProbability0->setDecimals(6);
        this->_spinBoxProbability0->setSingleStep(0.01);
        this->_spinBoxProbability0->setValue(item->model()->status()->probability(0));
        this->connect(this->_spinBoxProbability0, SIGNAL(valueChanged(double)), this, SLOT(setItemProbability0(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxProbability0);
    }
}

void ParameterGOOperator::setItemProbability0(double value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->status()->setProbability(0, value);
}

void ParameterGOOperator::addProbability12Parameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Probability 1"), this));
        this->_spinBoxProbability1 = new QDoubleSpinBox(this);
        this->_spinBoxProbability1->setMinimum(0.0);
        this->_spinBoxProbability1->setMaximum(1.0);
        this->_spinBoxProbability1->setDecimals(6);
        this->_spinBoxProbability1->setSingleStep(0.01);
        this->_spinBoxProbability1->setValue(item->model()->status()->probability(1));
        this->connect(this->_spinBoxProbability1, SIGNAL(valueChanged(double)), this, SLOT(setItemProbability1(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxProbability1);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Probability 2"), this));
        this->_spinBoxProbability2 = new QDoubleSpinBox(this);
        this->_spinBoxProbability2->setMinimum(0.0);
        this->_spinBoxProbability2->setMaximum(1.0);
        this->_spinBoxProbability2->setDecimals(6);
        this->_spinBoxProbability2->setSingleStep(0.01);
        this->_spinBoxProbability2->setValue(item->model()->status()->probability(2));
        this->connect(this->_spinBoxProbability2, SIGNAL(valueChanged(double)), this, SLOT(setItemProbability2(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxProbability2);
    }
}

void ParameterGOOperator::setItemProbability1(double value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->status()->setProbability(1, value);
}

void ParameterGOOperator::setItemProbability2(double value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->status()->setProbability(2, value);
}

void ParameterGOOperator::addProbabilityMultipleParameter()
{
    if (0L != this->_item)
    {
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Probabilities"), this));
        this->_buttonMulitpleProbability = new QPushButton(this);
        this->_buttonMulitpleProbability->setText(tr("Click to edit"));
        this->connect(this->_buttonMulitpleProbability, SIGNAL(clicked()), this, SLOT(setItemMultipleProbability()));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_buttonMulitpleProbability);
    }
}

void ParameterGOOperator::setItemMultipleProbability()
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    DialogGOProbability *probabilitydialog = new DialogGOProbability(this);
    probabilitydialog->setModel(item->model());
    switch (item->model()->type())
    {
    case GOOperatorFactory::Operator_Type_1:
    case GOOperatorFactory::Operator_Type_3:
    case GOOperatorFactory::Operator_Type_6:
    case GOOperatorFactory::Operator_Type_7:
        probabilitydialog->setIsFixedNumber(true);
        break;
    default:
        break;
    }
    probabilitydialog->exec();
    delete probabilitydialog;
    if (this->_spinBoxProbability0)
    {
        this->_spinBoxProbability0->setValue(item->model()->status()->probability(0));
    }
    this->_spinBoxProbability1->setValue(item->model()->status()->probability(1));
    this->_spinBoxProbability2->setValue(item->model()->status()->probability(2));
}

void ParameterGOOperator::addOperator9XYParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        if (item->model()->parameter()->number() == 0)
        {
            item->model()->parameter()->setNumber(2);
            item->model()->parameter()->setParameter(0, 1.0);
            item->model()->parameter()->setParameter(1, 0.0);
        }

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("X"), this));
        this->_spinBox9X = new QSpinBox(this);
        this->_spinBox9X->setMinimum(-0x7fffffff);
        this->_spinBox9X->setMaximum(0x7fffffff);
        this->_spinBox9X->setValue(item->model()->parameter()->parameter(0));
        this->connect(this->_spinBox9X, SIGNAL(valueChanged(int)), this, SLOT(setItem9X(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox9X);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Y"), this));
        this->_spinBox9Y = new QSpinBox(this);
        this->_spinBox9Y->setMinimum(-0x7fffffff);
        this->_spinBox9Y->setMaximum(0x7fffffff);
        this->_spinBox9Y->setValue(item->model()->parameter()->parameter(1));
        this->connect(this->_spinBox9Y, SIGNAL(valueChanged(int)), this, SLOT(setItem9Y(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox9Y);
    }
}

void ParameterGOOperator::setItem9X(int value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->parameter()->setParameter(0, value);
}

void ParameterGOOperator::setItem9Y(int value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->parameter()->setParameter(1, value);
}

void ParameterGOOperator::addOperator11KParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        if (item->model()->parameter()->number() == 0)
        {
            item->model()->parameter()->setNumber(1);
            item->model()->parameter()->setParameter(0, 1.0);
        }

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("K"), this));
        this->_spinBox11K = new QSpinBox(this);
        this->_spinBox11K->setMinimum(0);
        this->_spinBox11K->setMaximum(item->model()->input()->number());
        this->_spinBox11K->setValue(item->model()->parameter()->parameter(0));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBox11K);
    }
}

void ParameterGOOperator::setItem11K(int value)
{
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    item->model()->parameter()->setParameter(0, value);
}
