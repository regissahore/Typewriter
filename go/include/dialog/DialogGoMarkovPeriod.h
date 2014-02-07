#ifndef DIALOGGOMARKOVPERIOD_H
#define DIALOGGOMARKOVPERIOD_H
#include <QDialog>

namespace Ui {
class DialogGoMarkovPeriod;
}

class DialogGoMarkovPeriod : public QDialog
{
    Q_OBJECT
public:
    explicit DialogGoMarkovPeriod(QWidget *parent = 0);
    ~DialogGoMarkovPeriod();
    double totalTime() const;
    int count() const;
    void setTotalTime(const double value);
    void setCount(const int value);
    
private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_totalSpinBox_valueChanged(double value);
    void on_intervalSpinBox_valueChanged(double value);
    void on_loopSpinBox_valueChanged(int value);
    void on_intervalSpinBox_editingFinished();

private:
    Ui::DialogGoMarkovPeriod *ui;
};

#endif // DIALOGGOMARKOVPERIOD_H
