#ifndef DIALOGGOMARKOVPERIOD_H
#define DIALOGGOMARKOVPERIOD_H
/**
 * The dialog for setting the total time and loop time for GO Markov repairable system.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDialog>

namespace Ui {
class DialogGOMarkovPeriod;
}

class DialogGOMarkovPeriod : public QDialog
{
    Q_OBJECT
public:
    explicit DialogGOMarkovPeriod(QWidget *parent = 0);
    ~DialogGOMarkovPeriod();
    double totalTime() const;
    int count() const;
    
private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_totalSpinBox_valueChanged(double value);
    void on_intervalSpinBox_valueChanged(double value);
    void on_loopSpinBox_valueChanged(int value);
    void on_intervalSpinBox_editingFinished();

private:
    Ui::DialogGOMarkovPeriod *ui;
};

#endif // DIALOGGOMARKOVPERIOD_H
