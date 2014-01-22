#ifndef DOCKMESSAGE_H
#define DOCKMESSAGE_H
#include <QTabWidget>
#include <QDockWidget>
#include <QGridLayout>
#include "messager.h"

class DebugConsole;
class OutputConsole;

class DockMessage : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockMessage(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

protected:
    DebugConsole *_debugConsole;
    OutputConsole *_outputConsole;
};

#endif // DOCKMESSAGE_H
