#ifndef DIALOGGOPROBABILITY_H
#define DIALOGGOPROBABILITY_H
/**
 * The dialog for editing the probablities of GO operators.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDialog>
#include <QList>
#include <QModelIndex>

class QString;
class QListView;
class QLineEdit;
class QDoubleSpinBox;
class QStandardItemModel;

class GOOperator;

class DialogGOProbability : public QDialog
{
    Q_OBJECT
public:
    DialogGOProbability(QWidget *parent = 0);
    void setModel(GOOperator *model);

protected:
    QDoubleSpinBox *_probabilitySpin;
    QLineEdit *_probabilityEdit;
    QListView *_probabilityView;
    QStandardItemModel *_probabilityModel;

    GOOperator *_model;
    QList<double> _probability;
    QList<QString> _description;
    int _currentIndex;

protected slots:
    void append();
    void removeEnd();
    void save();
    void changeIndex(QModelIndex modelIndex);

private:
    QString getProbabilityString(int index);
};

#endif // DIALOGGOPROBABILITY_H
