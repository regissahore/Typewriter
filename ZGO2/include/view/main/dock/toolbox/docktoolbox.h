#ifndef DOCKTOOLBOX_H
#define DOCKTOOLBOX_H
/**
 * 工具悬停窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDockWidget>
#include "messager.h"
#include "definationeditortype.h"
#include "messagefactoryeditor.h"

class DockToolbox : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockToolbox(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);
};

#endif // DOCKTOOLBOX_H
