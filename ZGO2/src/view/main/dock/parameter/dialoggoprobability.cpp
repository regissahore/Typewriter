#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QDoubleSpinBox>
#include <QStandardItemModel>
#include "dialoggoprobability.h"
#include "gooperator.h"
#include "gostatus.h"
#include "bigdecimal.h"

DialogGOProbability::DialogGOProbability(QWidget *parent) : QDialog(parent)
{
    this->_currentIndex = -1;
    this->_model = 0L;

    this->setWindowTitle(tr("Edit Status Probability"));
    this->setGeometry(this->x(), this->y(), 450, 240);
    QHBoxLayout *mainLayout = new QHBoxLayout();
    this->setLayout(mainLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout();
    mainLayout->addLayout(leftLayout);
    this->_probabilityView = new QListView(this);
    this->_probabilityModel = new QStandardItemModel(this);
    _probabilityView->setModel(this->_probabilityModel);
    this->connect(_probabilityView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeIndex(QModelIndex)));
    leftLayout->addWidget(_probabilityView);
    this->_appendButton = new QPushButton(this);
    _appendButton->setText(tr("Append"));
    this->connect(_appendButton, SIGNAL(clicked()), this, SLOT(append()));
    leftLayout->addWidget(_appendButton);
    this->_removeButton = new QPushButton(this);
    _removeButton->setText(tr("Remove End"));
    this->connect(_removeButton, SIGNAL(clicked()), this, SLOT(removeEnd()));
    leftLayout->addWidget(_removeButton);

    QGridLayout *rightLayout = new QGridLayout();
    mainLayout->addLayout(rightLayout);
    QLabel *statusLabel = new QLabel(this);
    statusLabel->setText(tr("Status Probability"));
    statusLabel->setAlignment(Qt::AlignRight);
    rightLayout->addWidget(statusLabel, 0, 0);
    this->_probabilitySpin = new QDoubleSpinBox(this);
    _probabilitySpin->setMinimum(0.0);
    _probabilitySpin->setMaximum(1.0);
    _probabilitySpin->setDecimals(6);
    this->connect(_probabilitySpin, SIGNAL(valueChanged(QString)), this, SLOT(updateView(QString)));
    rightLayout->addWidget(_probabilitySpin, 0, 1);
    QLabel *descLabel = new QLabel(this);
    descLabel->setText(tr("Description"));
    descLabel->setAlignment(Qt::AlignRight);
    rightLayout->addWidget(descLabel, 1, 0);
    this->_probabilityEdit = new QLineEdit(this);
    this->connect(this->_probabilityEdit, SIGNAL(textChanged(QString)), this, SLOT(updateView(QString)));
    rightLayout->addWidget(_probabilityEdit, 1, 1);
    rightLayout->setRowStretch(2, 100);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    rightLayout->addLayout(buttonLayout, 3, 1);
    QPushButton *confirmButton = new QPushButton(this);
    confirmButton->setText(tr("Confirm"));
    confirmButton->setDefault(true);
    this->connect(confirmButton, SIGNAL(clicked()), this, SLOT(save()));
    buttonLayout->addWidget(confirmButton);
    QPushButton *cancelButton = new QPushButton(this);
    cancelButton->setText(tr("Cancel"));
    this->connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    buttonLayout->addWidget(cancelButton);
}

QString DialogGOProbability::getProbabilityString(int index)
{
    if (index >= 0 && index < this->_probability.size())
    {
        return QString("[%1] %2 " + this->_description[index]).arg(index).arg(this->_probability[index]);
    }
    return tr("Error: Out of index");
}

QString DialogGOProbability::getCurrentProbabilityString(int index)
{
    return QString("[%1] %2 " + this->_probabilityEdit->text()).arg(index).arg(this->_probabilitySpin->value());
}

/**
 * The model must be set before exec the dialog.
 * @param model The GOOperator.
 */
void DialogGOProbability::setModel(GOOperator *model)
{
    this->_model = model;
    this->_probability.clear();
    this->_description.clear();
    this->_probabilityModel->clear();
    for (int i = 0; i < model->status()->number(); ++i)
    {
        this->_probability.append(model->status()->probability(i).toString().toFloat());
        this->_description.append(model->status()->description(i));
        this->_probabilityModel->appendRow(new QStandardItem(this->getProbabilityString(i)));
    }
    if (model->status()->number() >= 0)
    {
        this->changeIndex(this->_probabilityModel->index(0, 0));
    }
}

/**
 * Set if the number of status is editable.
 * @param The value is true when the number of status is unfixed.
 */
void DialogGOProbability::setIsFixedNumber(bool value)
{
    if (value)
    {
        this->_appendButton->setEnabled(false);
        this->_removeButton->setEnabled(false);
    }
}

void DialogGOProbability::append()
{
    this->_probability.append(0.0);
    this->_description.append("");
    this->_probabilityModel->appendRow(new QStandardItem(this->getProbabilityString(this->_probabilityModel->rowCount())));
    if (this->_probabilityModel->rowCount() == 1)
    {
        this->changeIndex(this->_probabilityModel->index(0, 0));
        this->_probabilitySpin->setEnabled(true);
        this->_probabilityEdit->setEnabled(true);
    }
    this->changeIndex(this->_probabilityModel->index(this->_probabilityModel->rowCount() - 1, 0));
}

void DialogGOProbability::removeEnd()
{
    this->_probability.removeLast();
    this->_description.removeLast();
    this->_probabilityModel->removeRow(this->_probabilityModel->rowCount() - 1);
    if (this->_currentIndex >= this->_probabilityModel->rowCount())
    {
        if (this->_probabilityModel->rowCount() != 0)
        {
            this->changeIndex(this->_probabilityModel->index(this->_probabilityModel->rowCount() - 1, 0));
        }
    }
    if (this->_probabilityModel->rowCount() == 0)
    {
        this->_probabilitySpin->setValue(0.0);
        this->_probabilityEdit->setText("");
        this->_probabilitySpin->setEnabled(false);
        this->_probabilityEdit->setEnabled(false);
    }
}

void DialogGOProbability::save()
{
    if (this->_currentIndex >= 0 && this->_currentIndex < this->_probability.size())
    {
        this->_probability[this->_currentIndex] = this->_probabilitySpin->value();
        this->_description[this->_currentIndex] = this->_probabilityEdit->text();
        this->_probabilityModel->setItem(this->_currentIndex, new QStandardItem(this->getProbabilityString(this->_currentIndex)));
    }
    this->_model->status()->setNumber(this->_probability.size());
    for (int i = 0; i < this->_probability.size(); ++i)
    {
        this->_model->status()->setProbability(i, BigDecimal::valueOf(this->_probability[i]));
        this->_model->status()->setDescription(i, this->_description[i]);
    }
    this->accept();
}

void DialogGOProbability::changeIndex(QModelIndex modelIndex)
{
    int index = modelIndex.row();
    if (index != this->_currentIndex && index != -1)
    {
        if (this->_currentIndex >= 0 && this->_currentIndex < this->_probability.size())
        {
            this->_probability[this->_currentIndex] = this->_probabilitySpin->value();
            this->_description[this->_currentIndex] = this->_probabilityEdit->text();
            this->_probabilityModel->setItem(this->_currentIndex, new QStandardItem(this->getProbabilityString(this->_currentIndex)));
        }
        this->_currentIndex = index;
        this->_probabilitySpin->setValue(this->_probability[index]);
        this->_probabilityEdit->setText(this->_description[index]);
        this->_probabilityView->setCurrentIndex(modelIndex);
    }
}

void DialogGOProbability::updateView(QString)
{
    if (this->_currentIndex >= 0 && this->_currentIndex < this->_probabilityModel->rowCount())
    {
        this->_probabilityModel->setItem(this->_currentIndex, new QStandardItem(this->getCurrentProbabilityString(this->_currentIndex)));
    }
}
