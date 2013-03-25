#ifndef PARAMETERABSTRACT_H
#define PARAMETERABSTRACT_H
/**
 * The abstract parameter widget.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QTableView>

class QStandardItemModel;

class ParameterAbstract : public QTableView
{
    Q_OBJECT
public:
    ParameterAbstract(QWidget *parent = 0);
    void* dataItem() const;
    void setDataItem(void *dataItem);

protected:
    QStandardItemModel *_model;
    void *_dataItem;
};

#endif // PARAMETERABSTRACT_H
