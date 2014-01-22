#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include "ParameterGoSignal.h"
#include "ItemGoSignal.h"
#include "ItemGoOperator.h"
#include "GoOperator.h"

ParameterGoSignal::ParameterGoSignal(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGoSignal::bindItem(void *item)
{
    this->_item = item;
    this->addSignalParameter();
}

void ParameterGoSignal::addIDParameter()
{
    if (0L != this->_item)
    {
        ItemGoSignal *item = (ItemGoSignal*)this->_item;
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

void ParameterGoSignal::setItemID(int value)
{
    ItemGoSignal *item = (ItemGoSignal*)this->_item;
    item->model()->setId(value);
    item->update();
}

void ParameterGoSignal::addSignalParameter()
{
    if (0L != this->_item)
    {
        this->addIDParameter();

        ItemGoSignal *item = (ItemGoSignal*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Operator 1"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(QString("%1").arg(item->start()->op->model()->id()), this));

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Operator 2"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(QString("%1").arg(item->end()->op->model()->id()), this));

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Is Straight"), this));
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->setChecked(item->isStraightLine());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setIsStraightLine(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Global Feedback"), this));
        checkBox = new QCheckBox(this);
        checkBox->setChecked(item->model()->isGlobalFeedback());
        this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setIsGlobalFeedback(bool)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
    }
}

void ParameterGoSignal::setIsStraightLine(bool value)
{
    ItemGoSignal *signal = (ItemGoSignal*)this->_item;
    signal->setIsStraightLine(value);
    signal->update();
}

void ParameterGoSignal::setIsGlobalFeedback(bool value)
{
    ItemGoSignal *signal = (ItemGoSignal*)this->_item;
    signal->model()->setIsGlobalFeedback(value);
    signal->update();
}
