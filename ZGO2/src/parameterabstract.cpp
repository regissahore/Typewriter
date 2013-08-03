#include <QLabel>
#include <QSpinBox>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include "parameterabstract.h"
#include "itemdrawable.h"
#include "identifieditem.h"

ParameterAbstract::ParameterAbstract(QWidget *parent) : QWidget(parent), Messager()
{
    this->_item = 0L;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
    this->_tableWidget = new QTableWidget(this);
    this->_tableWidget->horizontalHeader()->setStretchLastSection(true);
    this->_tableWidget->setColumnCount(2);
    this->_tableWidget->setRowCount(0);
    QStringList header;
    header.append(tr("Parameter"));
    header.append(tr("Value"));
    this->_tableWidget->setHorizontalHeaderLabels(header);
    this->_tableWidget->verticalHeader()->hide();
    this->resize(130, 400);
    layout->addWidget(this->_tableWidget);
}

ParameterAbstract::~ParameterAbstract()
{
    this->Messager::~Messager();
}

void ParameterAbstract::bindItem(void *item)
{
    this->_item = item;
}

void ParameterAbstract::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}

void ParameterAbstract::addPositionParameter()
{
    if (0L != this->_item)
    {
        ItemDrawable *item = (ItemDrawable*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("X Position"), this));
        this->_spinBoxPosX = new QDoubleSpinBox(this);
        this->_spinBoxPosX->setMinimum(-1e100);
        this->_spinBoxPosX->setMaximum(1e100);
        this->_spinBoxPosX->setDecimals(2);
        this->_spinBoxPosX->setValue(item->pos().x());
        this->connect(this->_spinBoxPosX, SIGNAL(valueChanged(double)), this, SLOT(setItemPosX(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxPosX);
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Y Position"), this));
        this->_spinBoxPosY = new QDoubleSpinBox(this);
        this->_spinBoxPosY->setMinimum(-1e100);
        this->_spinBoxPosY->setMaximum(1e100);
        this->_spinBoxPosY->setDecimals(2);
        this->_spinBoxPosY->setValue(item->pos().y());
        this->connect(this->_spinBoxPosY, SIGNAL(valueChanged(double)), this, SLOT(setItemPosY(double)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxPosY);
    }
}

void ParameterAbstract::setItemPosX(double value)
{
    ItemDrawable *item = (ItemDrawable*)this->_item;
    item->setX(value);
}

void ParameterAbstract::setItemPosY(double value)
{
    ItemDrawable *item = (ItemDrawable*)this->_item;
    item->setY(value);
}

void ParameterAbstract::addIDParameter()
{
    if (0L != this->_item)
    {
        IdentifiedItem *item = (IdentifiedItem*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("ID"), this));
        this->_spinBoxID = new QSpinBox(this);
        this->_spinBoxID->setMinimum(1);
        this->_spinBoxID->setMaximum(0x7fffffff);
        this->_spinBoxID->setValue(item->id());
        this->connect(this->_spinBoxID, SIGNAL(valueChanged(int)), this, SLOT(setItemID(int)));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, this->_spinBoxID);
    }
}

void ParameterAbstract::setItemID(int value)
{
    ((IdentifiedItem*)this->_item)->setId(value);
    ((ItemDrawable*)this->_item)->update();
}

void ParameterAbstract::addTypeParameter()
{
    if (0L != this->_item)
    {
        TypedItem *item = (TypedItem*)this->_item;
        this->_tableWidget->insertRow(this->_tableWidget->rowCount());
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 0, new QLabel(tr("Type"), this));
        this->_tableWidget->setCellWidget(this->_tableWidget->rowCount() - 1, 1, new QLabel(QString("%1").arg(item->TypedItem::type()), this));
    }
}
