#include <QLabel>
#include <QLineEdit>
#include "parametergotext.h"
#include "itemgotext.h"
#include "tablewidgetgoitem.h"

ParameterGOText::ParameterGOText(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGOText::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addTextParameter();
}

void ParameterGOText::addTextParameter()
{
    if (0L != this->_item)
    {
        ItemGOText *item = (ItemGOText*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Text"), this));
        this->_lineEditText = new QLineEdit(this);
        this->_lineEditText->setText(item->text());
        this->connect(this->_lineEditText, SIGNAL(textChanged(QString)), this, SLOT(setItemText(QString)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_lineEditText);
    }
}

void ParameterGOText::setItemText(QString value)
{
    ItemGOText *item = (ItemGOText*)this->_item;
    item->setText(value);
}
