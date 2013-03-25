#include "dialogstringinput.h"

DialogStringInput::DialogStringInput(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    this->setLayout(vBoxLayout);
    this->_textLabel = new QLabel(tr("Input a integer: "), this);
    vBoxLayout->addWidget(this->_textLabel);
    this->_stringInput = new QLineEdit(this);
    vBoxLayout->addWidget(this->_stringInput);
    QWidget *widget = new QWidget(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(widget);
    widget->setLayout(hBoxLayout);
    vBoxLayout->addWidget(widget);
    QSpacerItem *spacer = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hBoxLayout->addItem(spacer);
    QPushButton *confirmButton = new QPushButton(tr("Confirm"), this);
    confirmButton->setDefault(true);
    this->connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
    hBoxLayout->addWidget(confirmButton);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    this->connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    hBoxLayout->addWidget(cancelButton);
}

/**
 * Set the display text.
 * @param text The text to be displayed.
 */
void DialogStringInput::setText(const QString text)
{
    this->_textLabel->setText(text);
}

/**
 * Get the spinbox of integer input.
 * @return QSpinBox.
 */
QLineEdit* DialogStringInput::stringInput() const
{
    return this->_stringInput;
}

/**
 * The integer is confirmed.
 */
void DialogStringInput::confirm()
{
    this->accept();
}

/**
 * The input is canceled.
 */
void DialogStringInput::cancel()
{
    this->reject();
}
