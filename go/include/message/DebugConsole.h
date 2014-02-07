#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H
#include <memory>
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include "Messager.h"

class DebugConsole : public QWidget, public Messager
{
    Q_OBJECT
public:
    explicit DebugConsole(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(std::shared_ptr<Message> message);

protected:
    QTextEdit *_textEdit;

private slots:
    void decreaseText();
};

#endif // DEBUGCONSOLE_H
