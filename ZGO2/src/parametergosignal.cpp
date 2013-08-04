#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include "parametergosignal.h"
#include "itemgosignal.h"
#include "itemgooperator.h"
#include "gooperator.h"

ParameterGOSignal::ParameterGOSignal(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOSignal::bindItem(void *item)
{
    this->_item = item;
    this->addSignalParameter();
}

void ParameterGOSignal::addIDParameter()
{
    if (0L != this->_item)
    {
        ItemGOSignal *item = (ItemGOSignal*)this->_item;
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

void ParameterGOSignal::setItemID(int value)
{
    ItemGOSignal *item = (ItemGOSignal*)this->_item;
    item->model()->setId(value);
    item->update();
}

void ParameterGOSignal::addSignalParameter()
{
    if (0L != this->_item)
    {
        this->addIDParameter();

        ItemGOSignal *item = (ItemGOSignal*)this->_item;
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
    }
}

void ParameterGOSignal::setIsStraightLine(bool value)
{
    ItemGOSignal *signal = (ItemGOSignal*)this->_item;
    signal->setIsStraightLine(value);
    signal->update();
}
