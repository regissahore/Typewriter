#ifndef DOCKMESSAGE_H
#define DOCKMESSAGE_H
#include <QTabWidget>
#include <QDockWidget>
#include <QGridLayout>
#include "Messager.h"

class OutputConsole;

class DockMessage : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockMessage(QWidget *parent = 0);
    void bindMessage();

protected:
    OutputConsole *_outputConsole;
};

#endif // DOCKMESSAGE_H
