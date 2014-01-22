#include "dialogintegerinput.h"

DialogIntegerInput::DialogIntegerInput(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    this->setLayout(vBoxLayout);
    this->_textLabel = new QLabel(tr("Input a integer: "), this);
    vBoxLayout->addWidget(this->_textLabel);
    this->_integerInput = new QSpinBox(this);
    this->_integerInput->setMinimum(0);
    this->_integerInput->setMaximum(65535);
    vBoxLayout->addWidget(this->_integerInput);
    QWidget *widget = new QWidget(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(widget);
    widget->setLayout(hBoxLayout);
    vBoxLayout->addWidget(widget);
    QSpacerItem *spacer = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hBoxLayout->addItem(spacer);
    QPushButton *confirmButton = new QPushButton(tr("Confirm"), this);
    confirmButton->setDefault(true);
    this->connect(confirmButton, SIGNAL(clicked()), this, SLOT(accept()));
    hBoxLayout->addWidget(confirmButton);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    this->connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    hBoxLayout->addWidget(cancelButton);
}

void DialogIntegerInput::setText(const QString text)
{
    this->_textLabel->setText(text);
}

QSpinBox* DialogIntegerInput::integerInput() const
{
    return this->_integerInput;
}
