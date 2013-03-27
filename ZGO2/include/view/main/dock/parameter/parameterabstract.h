#ifndef PARAMETERABSTRACT_H
#define PARAMETERABSTRACT_H
/**
 * The abstract parameter widget.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QTableWidget>

class ParameterAbstract : public QWidget
{
    Q_OBJECT
public:
    ParameterAbstract(QWidget *parent = 0);
    virtual void bindItem(void* item);

protected:
    QTableWidget *_tableWidget;
    void* _item;
    void addPositionParameter();
    void addIDParameter();
    void addTypeParameter();

protected slots:
    virtual void itemChanged(QTableWidgetItem *tableItem);
};

#endif // PARAMETERABSTRACT_H
