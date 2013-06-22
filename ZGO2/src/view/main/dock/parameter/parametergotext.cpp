#include "parametergotext.h"
#include "itemgotext.h"
#include "tablewidgetgoitem.h"

ParameterGOText::ParameterGOText(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOText::bindItem(void *item)
{
    this->_item = item;
    this->_tableWidget->disconnect();
    while (this->_tableWidget->rowCount())
    {
        this->_tableWidget->removeRow(0);
    }
    this->addPositionParameter();
    this->addTextParameter();
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOText::addTextParameter()
{
    if (0L != this->_item)
    {
        ItemGOText *item = (ItemGOText*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("Text"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(item->text());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_TEXT);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOText::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOText *item = (ItemGOText*)this->_item;
    float floatValue;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_POSITION_X:
        floatValue = goTableItem->text().toFloat();
        item->setX(floatValue);
        break;
    case TableWidgetGOItem::PARAMETER_POSITION_Y:
        floatValue = goTableItem->text().toFloat();
        item->setY(floatValue);
        break;
    case TableWidgetGOItem::PARAMETER_TEXT:
        item->setText(goTableItem->text());
        break;
    default:
        break;
    }
    item->update();
    this->bindItem(item);
}
