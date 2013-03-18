#ifndef DOCKMESSAGE_H
#define DOCKMESSAGE_H
/**
 * 用于消息的输出的悬停窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QTabWidget>
#include <QDockWidget>
#include <QGridLayout>
#include "messager.h"
#include "debugconsole.h"

class DockMessage : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockMessage(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

protected:
    DebugConsole *_debugConsole;
};

#endif // DOCKMESSAGE_H
