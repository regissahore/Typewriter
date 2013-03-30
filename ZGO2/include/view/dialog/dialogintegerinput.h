#ifndef DIALOGINTEGERINPUT_H
#define DIALOGINTEGERINPUT_H
/**
 * A dialog with an integer input.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QLabel>
#include <QDialog>
#include <QSpinBox>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class DialogIntegerInput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogIntegerInput(QWidget *parent = 0);
    void setText(const QString text);
    QSpinBox* integerInput() const;

private:
    QLabel *_textLabel;
    QSpinBox *_integerInput;
};

#endif // DIALOGINTEGERINPUT_H
