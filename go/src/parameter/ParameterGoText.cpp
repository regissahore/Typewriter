#include <QLabel>
#include <QLineEdit>
#include "ParameterGoText.h"
#include "ItemGoText.h"

ParameterGoText::ParameterGoText(QWidget *parent) : ParameterAbstract(parent)
{
}

void ParameterGoText::bindItem(void *item)
{
    this->_item = item;
    this->addPositionParameter();
    this->addTextParameter();
}

void ParameterGoText::addTextParameter()
{
    if (nullptr != this->_item)
    {
        ItemGoText *item = (ItemGoText*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Text"), this));
        this->_lineEditText = new QLineEdit(this);
        this->_lineEditText->setText(item->text());
        this->connect(this->_lineEditText, SIGNAL(textChanged(QString)), this, SLOT(setItemText(QString)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_lineEditText);
    }
}

void ParameterGoText::setItemText(QString value)
{
    ItemGoText *item = (ItemGoText*)this->_item;
    item->setText(value);
}
