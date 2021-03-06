#ifndef OUTPUTCONSOLE_H
#define OUTPUTCONSOLE_H
#include "stable.h"
#include "Messager.h"

namespace Ui {
class OutputConsole;
}

class OutputConsole : public QWidget, public Messager
{
    Q_OBJECT
    
public:
    explicit OutputConsole(QWidget *parent = 0);
    ~OutputConsole();
    void bindMessage();
    void messageEvent(QSharedPointer<Message> message);
    
private:
    Ui::OutputConsole *ui;
};

#endif // OUTPUTCONSOLE_H
