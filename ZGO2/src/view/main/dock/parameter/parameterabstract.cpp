#include <QStandardItemModel>
#include <QHeaderView>
#include "parameterabstract.h"

ParameterAbstract::ParameterAbstract(QWidget *parent) : QTableView(parent)
{
    this->_model = new QStandardItemModel(this);
    this->_model->setColumnCount(2);
    this->_model->setHeaderData(0, Qt::Horizontal, tr("Parameter"));
    this->_model->setHeaderData(1, Qt::Horizontal, tr("Value"));
    this->_model->setItem(0, 0, new QStandardItem("test"));
    this->setModel(this->_model);
    this->verticalHeader()->hide();
    this->setEditTriggers(QTableView::NoEditTriggers);
}

void* ParameterAbstract::dataItem() const
{
    return this->_dataItem;
}

void ParameterAbstract::setDataItem(void *dataItem)
{
    this->_dataItem = dataItem;
}
