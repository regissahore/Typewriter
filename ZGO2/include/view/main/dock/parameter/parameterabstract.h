#ifndef PARAMETERABSTRACT_H
#define PARAMETERABSTRACT_H
/**
 * The abstract parameter widget.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QTableWidget>
#include "messager.h"

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
    void addPositionParameter();
    void addIDParameter();
    void addTypeParameter();

protected slots:
    virtual void itemChanged(QTableWidgetItem *tableItem);
    virtual void itemClicked(QTableWidgetItem *tableItem);
};

#endif // PARAMETERABSTRACT_H
