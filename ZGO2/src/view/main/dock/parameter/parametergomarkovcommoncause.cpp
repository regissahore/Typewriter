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
    this->_tableWidget->disconnect();
    while (this->_tableWidget->rowCount())
    {
        this->_tableWidget->removeRow(0);
    }
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Common Cause"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->commonCause()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_COMMON_CAUSE);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    }
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOMarkovCommonCause::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOMarkovCommonCause *item = (ItemGOMarkovCommonCause*)this->_item;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_COMMON_CAUSE:
        item->model()->setCommonCause(goTableItem->text().toDouble());
    default:
        break;
    }
    item->update();
    this->bindItem(item);
}
