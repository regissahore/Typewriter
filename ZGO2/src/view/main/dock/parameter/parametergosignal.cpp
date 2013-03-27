#include "parametergosignal.h"
#include "tablewidgetgoitem.h"
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
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOSignal::addSignalParameter()
{
    if (0L != this->_item)
    {
        ItemGOSignal *item = (ItemGOSignal*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("Operator 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->start()->op->model()->id()));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Operator 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->end()->op->model()->id()));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("ID"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->id()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_ID);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOSignal::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOSignal *item = (ItemGOSignal*)this->_item;
    int intValue;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_ID:
        intValue = goTableItem->text().toInt();
        item->model()->setId(intValue);
        break;
    default:
        break;
    }
    item->update();
}
