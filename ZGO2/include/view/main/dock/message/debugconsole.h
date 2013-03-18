#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H
/**
 * 程序调试用的控制台。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include "messager.h"
#include "messagefactorymainwindow.h"
#include "messagefactoryeditor.h"
#include "messagefactorytool.h"

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
