#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include "messager.h"

class DebugConsole : public QWidget, public Messager
{
    Q_OBJECT
public:
    explicit DebugConsole(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(QSharedPointer<Message> message);

protected:
    QTextEdit *_textEdit;

private slots:
    void decreaseText();
};

#endif // DEBUGCONSOLE_H
