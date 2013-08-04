#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include "parametergomarkovchart.h"
#include "itemgomarkovchart.h"
#include "gomarkovchartdata.h"

ParameterGOMarkovChart::ParameterGOMarkovChart(QWidget* parent) : ParameterAbstract(parent)
{
}

void ParameterGOMarkovChart::bindItem(void *item)
{
    this->_item = item;
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;

    QLabel *label;
    QComboBox *comboBox;
    QCheckBox *checkBox;

    this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    label = new QLabel(this);
    label->setText(tr("Signal"));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    comboBox = new QComboBox(this);
    comboBox->setEditable(true);
    for (int i = 0; i < chart->chartData()->names.size(); ++i)
    {
        comboBox->addItem(chart->chartData()->names[i]);
    }
    this->connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setDisplayItem(QString)));
            this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, comboBox);

    this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    label = new QLabel(this);
    label->setText(tr("Display P"));
    label->setStyleSheet("QLabel{color:darkgreen;}");
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(chart->isDisplayP());
    this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setDisplayP(bool)));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

    this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    label = new QLabel(this);
    label->setText(tr("Display Q"));
    label->setStyleSheet("QLabel{color:darkred;}");
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(chart->isDisplayQ());
    this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setDisplayQ(bool)));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

    this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    label = new QLabel(this);
    label->setText(tr("Display Lambda"));
    label->setStyleSheet("QLabel{color:darkblue;}");
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(chart->isDisplayLambda());
    this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setDisplayLambda(bool)));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);

    this->_tableWidget->insertRow(this->_tableWidget->rowCount());
    label = new QLabel(this);
    label->setText(tr("Display Mu"));
    label->setStyleSheet("QLabel{color:rgb(170, 170, 0);}");
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    checkBox = new QCheckBox(this);
    checkBox->setChecked(chart->isDisplayMu());
    this->connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(setDisplayMu(bool)));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, checkBox);
}

void ParameterGOMarkovChart::setDisplayItem(QString name)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setDisplayItem(name);
}

void ParameterGOMarkovChart::setDisplayP(bool value)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setIsDisplayP(value);
    chart->update();
}

void ParameterGOMarkovChart::setDisplayQ(bool value)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setIsDisplayQ(value);
    chart->update();
}

void ParameterGOMarkovChart::setDisplayLambda(bool value)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setIsDisplayLambda(value);
    chart->update();
}

void ParameterGOMarkovChart::setDisplayMu(bool value)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setIsDisplayMu(value);
    chart->update();
}
