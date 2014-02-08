#ifndef DOCKPARAMETER_H
#define DOCKPARAMETER_H
#include <QSharedPointer>
#include <QDockWidget>
#include "Messager.h"

class QVBoxLayout;
class ParameterAbstract;
class ItemDrawable;

class DockParameter : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    DockParameter(QWidget *parent = 0);
    ~DockParameter();
    void bindMessage();
    void messageEvent(QSharedPointer<Message> message);

private:
    ParameterAbstract *_parameter;
    QVBoxLayout *_layout;
    void changeParameter(ItemDrawable *item);
};

#endif // DOCKPARAMETER_H
