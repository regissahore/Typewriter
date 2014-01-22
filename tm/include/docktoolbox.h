#ifndef DOCKTOOLBOX_H
#define DOCKTOOLBOX_H
#include <QDockWidget>
#include "messager.h"
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
    void messageEvent(QSharedPointer<Message> message);

protected:
    ToolboxAbstract *_toolbox;
    void clear();
    void setToolbox(int editorType);
};

#endif // DOCKTOOLBOX_H
