#include <QVector>
#include <QTableWidgetItem>
#include "dialog13ainput.h"
#include "gomarkovoperator13.h"
#include "ui_dialogmatrixinput.h"

Dialog13AInput::Dialog13AInput(QWidget *parent) : DialogMatrixInput(parent)
{
}

void Dialog13AInput::setOperator(GOMarkovOperator13* op)
{
    this->_op = op;
    QVector<QVector<double> > *relation = op->relation();
    int inputNum = relation->size();
    int outputNum = 0;
    if (inputNum)
    {
        outputNum = relation->at(0).size();
    }
    this->ui->tableData->setRowCount(inputNum);
    this->ui->tableData->setColumnCount(outputNum);
    for (int i = 0; i < inputNum; ++i)
    {
        for (int j = 0; j < outputNum; ++j)
        {
            this->ui->tableData->setItem(i, j, new QTableWidgetItem(QString("%1").arg(relation->at(i).at(j))));
        }
    }
}

void Dialog13AInput::saveChange()
{
    QVector<QVector<double> > *relation = this->_op->relation();
    for (int i = 0; i < relation->size(); ++i)
    {
        for (int j = 0; j < relation->at(i).size(); ++j)
        {
            (*relation)[i][j] = this->ui->tableData->item(i, j)->text().toDouble();
        }
    }
}
