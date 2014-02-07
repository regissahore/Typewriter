#ifndef DIALOGGOPROBABILITY_H
#define DIALOGGOPROBABILITY_H
#include <QDialog>
#include <QList>
#include <QModelIndex>

class QString;
class QListView;
class QLineEdit;
class QPushButton;
class QDoubleSpinBox;
class QStandardItemModel;

class GoOperator;

class DialogGoProbability : public QDialog
{
    Q_OBJECT
public:
    DialogGoProbability(QWidget *parent = 0);
    void setModel(GoOperator *model);
    void setIsFixedNumber(bool value);

protected:
    QDoubleSpinBox *_probabilitySpin;
    QLineEdit *_probabilityEdit;
    QListView *_probabilityView;
    QStandardItemModel *_probabilityModel;
    QPushButton *_appendButton;
    QPushButton *_removeButton;

    GoOperator *_model;
    QList<double> _probability;
    QList<QString> _description;
    int _currentIndex;

protected slots:
    void updateView(QString);
    void append();
    void removeEnd();
    void save();
    void changeIndex(QModelIndex modelIndex);

private:
    QString getProbabilityString(int index);
    QString getCurrentProbabilityString(int index);
};

#endif // DIALOGGOPROBABILITY_H
