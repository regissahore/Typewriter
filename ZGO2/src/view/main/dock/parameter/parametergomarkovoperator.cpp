#include "parametergomarkovoperator.h"
#include "itemgomarkovoperator.h"
#include "gomarkovoperator.h"
#include "gooperatorfactory.h"
#include "gomarkovstatus.h"
#include "tablewidgetgoitem.h"
#include "gostatus.h"

ParameterGOMarkovOperator::ParameterGOMarkovOperator(QWidget *parent) : ParameterGOOperator(parent)
{
}

void ParameterGOMarkovOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGOMarkovOperator *op = (ItemGOMarkovOperator*)item;
    switch (op->model()->type())
    {
    case GOOperatorFactory::Operator_Type_1:
        this->addMarkovParameter();
        break;
    case GOOperatorFactory::Operator_Type_2:
        break;
    case GOOperatorFactory::Operator_Type_3:
        this->addMarkovParameter();
        break;
    case GOOperatorFactory::Operator_Type_5:
        this->addMarkovParameter();
        break;
    case GOOperatorFactory::Operator_Type_6:
        this->addMarkovParameter();
        break;
    case GOOperatorFactory::Operator_Type_7:
        this->addMarkovParameter();
        break;
    case GOOperatorFactory::Operator_Type_10:
        break;
    case GOOperatorFactory::Operator_Type_11:
        this->addOperator11KParameter();
        break;
    default:
        break;
    }
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
    this->connect(this->_tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(itemClicked(QTableWidgetItem*)));
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

void ParameterGOMarkovOperator::itemChanged(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOMarkovOperator *item = (ItemGOMarkovOperator*)this->_item;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_FAILURE:
        ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyBreakdown(tableItem->text());
        item->model()->status()->setProbability(1, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityNormal());
        item->model()->status()->setProbability(2, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityBreakdown());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR:
        ((GOMarkovOperator*)item->model())->markovStatus()->setFrequencyRepair(tableItem->text());
        item->model()->status()->setProbability(1, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityNormal());
        item->model()->status()->setProbability(2, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityBreakdown());
        break;
    case TableWidgetGOItem::PARAMETER_GO_MARKOV_REPAIR_TIME:
        ((GOMarkovOperator*)item->model())->markovStatus()->setRepairTime(tableItem->text());
        item->model()->status()->setProbability(1, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityNormal());
        item->model()->status()->setProbability(2, ((GOMarkovOperator*)item->model())->markovStatus()->probabilityBreakdown());
        break;
    default:
        break;
    }
    this->ParameterGOOperator::itemChanged(tableItem);
}
