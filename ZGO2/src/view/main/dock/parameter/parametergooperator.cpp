#include "parametergooperator.h"
#include "tablewidgetgoitem.h"
#include "itemgooperator.h"
#include "gooperator.h"
#include "gostatus.h"

ParameterGOOperator::ParameterGOOperator(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    this->addStatusParameter();
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOOperator::addOperatorParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("ID"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->id()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_ID);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Type"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->type()));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOOperator::addStatusParameter()
{
    if (0L != this->_item)
    {
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("Status 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->probability(1)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_STATUS_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Description 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->description(1)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_DESCRIPTION_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Status 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->probability(2)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_STATUS_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Description 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->description(2)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_DESCRIPTION_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOOperator::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    int intValue;
    float floatValue;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_ID:
        intValue = goTableItem->text().toInt();
        item->model()->setId(intValue);
        break;
    case TableWidgetGOItem::PARAMETER_STATUS_1:
        floatValue = goTableItem->text().toFloat();
        item->model()->status()->setProbability(1, floatValue);
        break;
    case TableWidgetGOItem::PARAMETER_STATUS_2:
        floatValue = goTableItem->text().toFloat();
        item->model()->status()->setProbability(2, floatValue);
        break;
    case TableWidgetGOItem::PARAMETER_DESCRIPTION_1:
        item->model()->status()->setDescription(1, goTableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_DESCRIPTION_2:
        item->model()->status()->setDescription(2, goTableItem->text());
        break;
    default:
        break;
    }
    item->update();
}
