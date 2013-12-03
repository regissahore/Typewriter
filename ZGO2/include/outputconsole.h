#ifndef OUTPUTCONSOLE_H
#define OUTPUTCONSOLE_H
/**
 * 用于显示分析过程的输出。
 * @author ZHG <CyberZHG@gmail.com>
 **/
#include <QWidget>
#include "messager.h"

namespace Ui {
class OutputConsole;
}

class OutputConsole : public QWidget, public Messager
{
    Q_OBJECT
    
public:
    explicit OutputConsole(QWidget *parent = 0);
    ~OutputConsole();
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);
    
private:
    Ui::OutputConsole *ui;
};

#endif // OUTPUTCONSOLE_H
