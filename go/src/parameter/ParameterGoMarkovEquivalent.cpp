#include <QLabel>
#include <QSpinBox>
#include "ParameterGoMarkovEquivalent.h"
#include "ItemGoMarkovEquivalent.h"
#include "GoMarkovEquivalent.h"

ParameterGoMarkovEquivalent::ParameterGoMarkovEquivalent(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGoMarkovEquivalent::bindItem(void *item)
{
    this->_item = item;
    if (nullptr != this->_item)
    {
        ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)this->_item;

        this->addIDParameter();

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Shutdown Relevant(I)"), this));
        this->_spinBoxI = new QSpinBox(this);
        this->_spinBoxI->setMinimum(0);
        this->_spinBoxI->setMaximum(0x7fffffff);
        this->_spinBoxI->setValue(item->model()->I());
        this->connect(this->_spinBoxI, SIGNAL(valueChanged(int)), this, SLOT(setItemI(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxI);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Maintenance Relevant(L)"), this));
        this->_spinBoxL = new QSpinBox(this);
        this->_spinBoxL->setMinimum(0);
        this->_spinBoxL->setMaximum(0x7fffffff);
        this->_spinBoxL->setValue(item->model()->L());
        this->connect(this->_spinBoxL, SIGNAL(valueChanged(int)), this, SLOT(setItemL(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxL);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Backup Relevant(J)"), this));
        this->_spinBoxJ = new QSpinBox(this);
        this->_spinBoxJ->setMinimum(0);
        this->_spinBoxJ->setMaximum(0x7fffffff);
        this->_spinBoxJ->setValue(item->model()->J());
        this->connect(this->_spinBoxJ, SIGNAL(valueChanged(int)), this, SLOT(setItemJ(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxJ);
    }
}

void ParameterGoMarkovEquivalent::setItemI(int value)
{
    ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)this->_item;
    item->model()->setI(value);
}

void ParameterGoMarkovEquivalent::setItemL(int value)
{
    ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)this->_item;
    item->model()->setL(value);
}

void ParameterGoMarkovEquivalent::setItemJ(int value)
{
    ItemGoMarkovEquivalent *item = (ItemGoMarkovEquivalent*)this->_item;
    item->model()->setJ(value);
}
