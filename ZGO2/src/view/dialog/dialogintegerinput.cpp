#include "dialogintegerinput.h"

/**
 * Constructor.
 * @param parent The parent widget.
 */
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
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    vBoxLayout->addLayout(hBoxLayout);
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
void DialogIntegerInput::setText(const QString text)
{
    this->_textLabel->setText(text);
}

/**
 * Get the spinbox of integer input.
 * @return QSpinBox.
 */
QSpinBox* DialogIntegerInput::integerInput() const
{
    return this->_integerInput;
}

/**
 * The integer is confirmed.
 */
void DialogIntegerInput::confirm()
{
    this->accept();
}

/**
 * The input is canceled.
 */
void DialogIntegerInput::cancel()
{
    this->reject();
}
