#ifndef DOCKTOOLBOX_H
#define DOCKTOOLBOX_H
/**
 * 工具悬停窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDockWidget>
#include "messager.h"
#include "definationeditortype.h"
#include "messagefactory.h"
#include "toolboxfactory.h"

class DockToolbox : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockToolbox(QWidget *parent = 0);
    ~DockToolbox();
    QSize sizeHint() const;
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    ToolboxAbstract *_toolbox;
    void clear();
    void setToolbox(int editorType);
};

#endif // DOCKTOOLBOX_H
