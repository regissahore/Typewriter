#include <QLabel>
#include <QSpinBox>
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
    label->setText(tr("Vector Index"));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, label);
    this->_spinVector = new QSpinBox(this);
    this->_spinVector->setMinimum(1);
    this->_spinVector->setMaximum(chart->chartData()->probabilities[chart->displayIndex()][0].length());
    this->connect(this->_spinVector, SIGNAL(valueChanged(int)), this, SLOT(setDisplayVectorIndex(int)));
    this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinVector);

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
    chart->setDisplayItem(name, 0);
    int index = chart->displayIndex();
    DoubleVector vector = chart->chartData()->probabilities[index][0];
    int length = vector.length();
    this->_spinVector->setMinimum(1);
    this->_spinVector->setMaximum(length);
}

void ParameterGOMarkovChart::setDisplayVectorIndex(int index)
{
    ItemGOMarkovChart *chart = (ItemGOMarkovChart*)this->_item;
    chart->setDisplayVectorIndex(index - 1);
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
