#include "DockMessage.h"
#include "OutputConsole.h"

DockMessage::DockMessage(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Message"));
    this->setFeatures(QDockWidget::DockWidgetMovable);
    QTabWidget *tabWidget = new QTabWidget(this);

    this->_outputConsole = new OutputConsole(this);
    this->_outputConsole->setGeometry(this->_outputConsole->x(), this->_outputConsole->y(),
                                      this->_outputConsole->width(), 100);
    tabWidget->addTab(this->_outputConsole, tr("Output"));

    this->setWidget(tabWidget);
}

void DockMessage::bindMessage(MessageController *controller)
{
    this->_outputConsole->bindMessage(controller);
}
