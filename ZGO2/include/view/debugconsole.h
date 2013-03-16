#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H
/**
 * 程序调试用的控制台。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include "controller/messager.h"
#include "controller/messagefactorymainwindow.h"
#include "controller/messagefactoryeditor.h"

class DebugConsole : public QWidget, public Messager
{
    Q_OBJECT
public:
    explicit DebugConsole(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    QTextEdit *_textEdit;

private slots:
    void decreaseText();
};

#endif // DEBUGCONSOLE_H
