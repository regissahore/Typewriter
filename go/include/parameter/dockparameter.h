#ifndef DOCKPARAMETER_H
#define DOCKPARAMETER_H
#include <memory>
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
    void bindMessage(MessageController *controller);
    void messageEvent(std::shared_ptr<Message> message);

private:
    ParameterAbstract *_parameter;
    QVBoxLayout *_layout;
    void changeParameter(ItemDrawable *item);
};

#endif // DOCKPARAMETER_H
