#include "parametergomarkovequivalent.h"
#include "tablewidgetgoitem.h"
#include "itemgomarkovequivalent.h"
#include "gomarkovequivalent.h"

ParameterGOMarkovEquivalent::ParameterGOMarkovEquivalent(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOMarkovEquivalent::bindItem(void *item)
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
        ItemGOMarkovEquivalent *item = (ItemGOMarkovEquivalent*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("ID"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->id()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_ID);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Shutdown Relevant(I)"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->I()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_I);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Maintenance Relevant(L)"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->L()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_L);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Backup Relevant(J)"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->J()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_J);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOMarkovEquivalent::itemChanged(QTableWidgetItem *tableItem)
{

    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOMarkovEquivalent *item = (ItemGOMarkovEquivalent*)this->_item;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_ID:
        item->setId(goTableItem->text().toInt());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_I:
        item->model()->setI(goTableItem->text().toInt());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_L:
        item->model()->setL(goTableItem->text().toInt());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_EQUIVALENT_J:
        item->model()->setJ(goTableItem->text().toInt());
        break;
    default:
        break;
    }
    item->update();
    this->bindItem(item);
}
