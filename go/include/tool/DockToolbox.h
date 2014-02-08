#ifndef DOCKTOOLBOX_H
#define DOCKTOOLBOX_H
#include <QSharedPointer>
#include <QDockWidget>
#include "Messager.h"
#include "MessageFactory.h"
#include "ToolboxFactory.h"

class DockToolbox : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    explicit DockToolbox(QWidget *parent = 0);
    ~DockToolbox();
    QSize sizeHint() const;
    void bindMessage();
    void messageEvent(QSharedPointer<Message> message);

protected:
    ToolboxAbstract *_toolbox;
    void clear();
    void setToolbox(int editorType);
};

#endif // DOCKTOOLBOX_H
