#include <QLabel>
#include <QDoubleSpinBox>
#include "parametergomarkovcommoncause.h"
#include "itemgomarkovcommoncause.h"
#include "gomarkovcommoncause.h"
#include "tablewidgetgoitem.h"

ParameterGOMarkovCommonCause::ParameterGOMarkovCommonCause(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOMarkovCommonCause::bindItem(void *item)
{
    this->_item = item;
    if (0L != this->_item)
    {
        ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Common Cause"), this));
        this->_spinBoxCommonCause = new QDoubleSpinBox(this);
        this->_spinBoxCommonCause->setMinimum(0.0);
        this->_spinBoxCommonCause->setMaximum(1e100);
        this->_spinBoxCommonCause->setSingleStep(0.01);
        this->_spinBoxCommonCause->setValue(item->model()->commonCause());
        this->connect(this->_spinBoxCommonCause, SIGNAL(valueChanged(double)), this, SLOT(setItemCommonCause(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxCommonCause);
    }
}

void ParameterGOMarkovCommonCause::setItemCommonCause(double value)
{
    ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
    item->model()->setCommonCause(value);
}
