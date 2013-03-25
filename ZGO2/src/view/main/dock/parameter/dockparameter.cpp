#include <QVBoxLayout>
#include "dockparameter.h"
#include "parameterabstract.h"

DockParameter::DockParameter(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Parameter"));
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->_parameter = new ParameterAbstract();
    this->setWidget(this->_parameter);
}

void DockParameter::bindMessage(MessageController *controller)
{
    //
}

void DockParameter::messageEvent(Message *message)
{
    //
}
