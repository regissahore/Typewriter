#include "parametergomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "gooperatorfactory.h"
#include "gomarkovstatus.h"
#include "tablewidgetgoitem.h"
#include "gostatus.h"
#include "messagefactory.h"
#include "goparameter.h"
#include "gomarkovoperator1e1.h"
#include "gomarkovoperatorfactory.h"

ParameterGOMarkovOperator::ParameterGOMarkovOperator(QWidget *parent) : ParameterGOOperator(parent)
{
}

void ParameterGOMarkovOperator::bindItem(void *item)
{
    this->_item = item;
    this->_tableWidget->disconnect();
    while (this->_tableWidget->rowCount())
    {
        this->_tableWidget->removeRow(0);
    }
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
    switch (op->model()->type())
    {
    case GOMarkovOperatorFactory::Operator_Type_1:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_2:
        break;
    case GOMarkovOperatorFactory::Operator_Type_3:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_5:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_6:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_7:
        this->addMarkovParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_9:
        this->addOperator9XYParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_10:
        break;
    case GOMarkovOperatorFactory::Operator_Type_11:
        this->addOperator11KParameter();
        break;
    case GOMarkovOperatorFactory::Operator_Type_1_E1:
        this->addMarkovMulti1Parameter();
        this->addMarkovMulti2Parameter();
        break;
    default:
        break;
    }
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
}

void ParameterGOMarkovOperator::addMarkovParameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Failure Rate"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator*)item->model())->markovStatus()->frequencyBreakdown().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Rate"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Time"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem((BigDecimal::one() / ( (GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair()).toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOMarkovOperator::addMarkovMulti1Parameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Failure Rate 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator*)item->model())->markovStatus()->frequencyBreakdown().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Rate 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Time 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem((BigDecimal::one() / ( (GOMarkovOperator*)item->model())->markovStatus()->frequencyRepair()).toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOMarkovOperator::addMarkovMulti2Parameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Failure Rate 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator1E1*)item->model())->markovStatus2()->frequencyBreakdown().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Rate 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(((GOMarkovOperator1E1*)item->model())->markovStatus2()->frequencyRepair().toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Repair Time 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem((BigDecimal::one() / ( (GOMarkovOperator1E1*)item->model())->markovStatus2()->frequencyRepair()).toString());
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOMarkovOperator::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE:
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE_1:
        ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyBreakdown(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR:
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_1:
        ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyRepair(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME:
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME_1:
        ((GOMarkovOperator*)item->model())->markovStatus()->setRepairTime(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE_2:
        ((GOMarkovOperator1E1*)item->model())->markovStatus2()->setFrequencyBreakdown(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_2:
        ((GOMarkovOperator1E1*)item->model())->markovStatus2()->setFrequencyRepair(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME_2:
        ((GOMarkovOperator1E1*)item->model())->markovStatus2()->setRepairTime(tableItem->text());
        break;
    case TableWidgetGOItem::PARAMETER_GO_9_X:
        item->model()->parameter()->setParameter(0, goTableItem->text().toInt());
        break;
    case TableWidgetGOItem::PARAMETER_GO_9_Y:
        item->model()->parameter()->setParameter(1, goTableItem->text().toInt());
        break;
    case TableWidgetGOItem::PARAMETER_GO_11_K:
        item->model()->parameter()->setParameter(0, goTableItem->text().toInt());
        break;
    default:
        break;
    }
    item->update();
    this->bindItem(item);
}
