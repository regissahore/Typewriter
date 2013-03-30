#include <QHeaderView>
#include <QVBoxLayout>
#include "parameterabstract.h"
#include "itemdrawable.h"
#include "tablewidgetgoitem.h"
#include "identifieditem.h"

ParameterAbstract::ParameterAbstract(QWidget *parent) : QWidget(parent)
{
    this->_item = 0L;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_tableWidget = new QTableWidget(this);
    this->_tableWidget->horizontalHeader()->setStretchLastSection(true);
    this->_tableWidget->setColumnCount(2);
    this->_tableWidget->setRowCount(0);
    QStringList header;
    header.append(tr("Parameter"));
    header.append(tr("Value"));
    this->_tableWidget->setHorizontalHeaderLabels(header);
    this->_tableWidget->verticalHeader()->hide();
    layout->addWidget(this->_tableWidget);
}

void ParameterAbstract::bindItem(void *item)
{
    this->_item = item;
}

void ParameterAbstract::addPositionParameter()
{
    if (0L != this->_item)
    {
        ItemDrawable *item = (ItemDrawable*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("X Position"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->pos().x()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_POSITION_X);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Y Position"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->pos().y()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_POSITION_Y);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterAbstract::addIDParameter()
{
    if (0L != this->_item)
    {
        IdentifiedItem *item = (IdentifiedItem*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("ID"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->id()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_ID);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterAbstract::addTypeParameter()
{
    if (0L != this->_item)
    {
        TypedItem *item = (TypedItem*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        TableWidgetGOItem *tableItem = new TableWidgetGOItem(tr("Type"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->TypedItem::type()));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_ID);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterAbstract::itemChanged(QTableWidgetItem *tableItem)
{
    Q_UNUSED(tableItem);
}

void ParameterAbstract::itemClicked(QTableWidgetItem *tableItem)
{
    Q_UNUSED(tableItem);
}
