#ifndef DOCKPARAMETER_H
#define DOCKPARAMETER_H
/**
 * The dock for setting the selection's parameter.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QDockWidget>
#include "messager.h"

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
    void messageEvent(QSharedPointer<Message> message);

private:
    ParameterAbstract *_parameter;
    QVBoxLayout *_layout;
    void changeParameter(ItemDrawable *item);
};

#endif // DOCKPARAMETER_H
