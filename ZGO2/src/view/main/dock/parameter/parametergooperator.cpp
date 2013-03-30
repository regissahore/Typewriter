#include "parametergooperator.h"
#include "tablewidgetgoitem.h"
#include "itemgooperator.h"
#include "gooperator.h"
#include "gostatus.h"
#include "gooperatorfactory.h"
#include "dialoggoprobability.h"

ParameterGOOperator::ParameterGOOperator(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOOperator::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addOperatorParameter();
    ItemGOOperator *op = (ItemGOOperator*)item;
    switch (op->model()->type())
    {
    case GOOperatorFactory::Operator_Type_1:
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_2:
        break;
    case GOOperatorFactory::Operator_Type_3:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_5:
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_6:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_7:
        this->addProbability0Parameter();
        this->addProbability12Parameter();
        this->addProbabilityMultipleParameter();
        break;
    case GOOperatorFactory::Operator_Type_10:
        break;
    default:
        break;
    }
    this->connect(this->_tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(itemChanged(QTableWidgetItem*)));
    this->connect(this->_tableWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(itemClicked(QTableWidgetItem*)));
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

void ParameterGOOperator::addProbability0Parameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Probability 0"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->probability(0)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_PROBABILITY_0);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOOperator::addProbability12Parameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        ItemGOOperator *item = (ItemGOOperator*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Probability 1"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->probability(1)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_PROBABILITY_1);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);

        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Probability 2"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(QString("%1").arg(item->model()->status()->probability(2)));
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_PROBABILITY_2);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOOperator::addProbabilityMultipleParameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Probabilities"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(tr("Click to edit"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_PROBABILITY_MULTIPLE);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 1, tableItem);
    }
}

void ParameterGOOperator::addOutputParameter()
{
    if (0L != this->_item)
    {
        TableWidgetGOItem *tableItem;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        tableItem = new TableWidgetGOItem(tr("Output"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        this->_tableWidget->setItem(this->_tableWidget->rowCount() - 1, 0, tableItem);
        tableItem = new TableWidgetGOItem(tr("Click to edit"));
        tableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        tableItem->setParameterType(TableWidgetGOItem::PARAMETER_OUTPUT);
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
    case TableWidgetGOItem::PARAMETER_POSITION_X:
        floatValue = goTableItem->text().toFloat();
        item->setX(floatValue);
    case TableWidgetGOItem::PARAMETER_POSITION_Y:
        floatValue = goTableItem->text().toFloat();
        item->setY(floatValue);
    case TableWidgetGOItem::PARAMETER_PROBABILITY_0:
        floatValue = goTableItem->text().toFloat();
        item->model()->status()->setProbability(0, floatValue);
    case TableWidgetGOItem::PARAMETER_PROBABILITY_1:
        floatValue = goTableItem->text().toFloat();
        item->model()->status()->setProbability(1, floatValue);
    case TableWidgetGOItem::PARAMETER_PROBABILITY_2:
        floatValue = goTableItem->text().toFloat();
        item->model()->status()->setProbability(2, floatValue);
    default:
        break;
    }
    item->update();
}

void ParameterGOOperator::itemClicked(QTableWidgetItem *tableItem)
{
    TableWidgetGOItem *goTableItem = (TableWidgetGOItem*)tableItem;
    ItemGOOperator *item = (ItemGOOperator*)this->_item;
    DialogGOProbability *probabilitydialog;
    switch (goTableItem->parameterType())
    {
    case TableWidgetGOItem::PARAMETER_PROBABILITY_MULTIPLE:
        probabilitydialog = new DialogGOProbability(this);
        probabilitydialog->setModel(item->model());
        switch (item->model()->type())
        {
        case GOOperatorFactory::Operator_Type_1:
            probabilitydialog->setIsFixedNumber(true);
            break;
        case GOOperatorFactory::Operator_Type_2:
            break;
        case GOOperatorFactory::Operator_Type_3:
            probabilitydialog->setIsFixedNumber(true);
            break;
        case GOOperatorFactory::Operator_Type_5:
            break;
        case GOOperatorFactory::Operator_Type_6:
            probabilitydialog->setIsFixedNumber(true);
            break;
        case GOOperatorFactory::Operator_Type_7:
            probabilitydialog->setIsFixedNumber(true);
            break;
        case GOOperatorFactory::Operator_Type_10:
            break;
        default:
            break;
        }
        probabilitydialog->exec();
        delete probabilitydialog;
        break;
    case TableWidgetGOItem::PARAMETER_OUTPUT:
        break;
    default:
        break;
    }
}
