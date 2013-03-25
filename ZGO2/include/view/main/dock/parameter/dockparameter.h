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

class DockParameter : public QDockWidget, public Messager
{
    Q_OBJECT
public:
    DockParameter(QWidget *parent = 0);
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

private:
    ParameterAbstract *_parameter;
    QVBoxLayout *_layout;
};

#endif // DOCKPARAMETER_H
