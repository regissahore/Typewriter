#ifndef PARAMETERABSTRACT_H
#define PARAMETERABSTRACT_H
#include <QWidget>
#include <QTableWidget>
#include "messager.h"

class QSpinBox;
class QDoubleSpinBox;

class ParameterAbstract : public QWidget, public Messager
{
    Q_OBJECT
public:
    ParameterAbstract(QWidget *parent = 0);
    ~ParameterAbstract();
    virtual void bindItem(void* item);
    void bindMessage(MessageController *controller);

protected:
    QTableWidget *_tableWidget;
    void* _item;

    QDoubleSpinBox *_spinBoxPosX;
    QDoubleSpinBox *_spinBoxPosY;
    QSpinBox *_spinBoxID;

    void addPositionParameter();
    virtual void addIDParameter();
    virtual void addTypeParameter();

protected slots:
    virtual void setItemPosX(double value);
    virtual void setItemPosY(double value);
    virtual void setItemID(int value);
};

#endif // PARAMETERABSTRACT_H
