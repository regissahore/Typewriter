#include "DockMessage.h"
#include "DebugConsole.h"
#include "OutputConsole.h"

//#define DEBUG

DockMessage::DockMessage(QWidget *parent) : QDockWidget(parent), Messager()
{
    this->setWindowTitle(tr("Message"));
    this->setFeatures(QDockWidget::DockWidgetMovable);
    QTabWidget *tabWidget = new QTabWidget(this);

#ifdef DEBUG
    this->_debugConsole = new DebugConsole();
    tabWidget->addTab(this->_debugConsole, tr("Debug"));
#endif
    this->_outputConsole = new OutputConsole(this);
    this->_outputConsole->setGeometry(this->_outputConsole->x(), this->_outputConsole->y(),
                                      this->_outputConsole->width(), 100);
    tabWidget->addTab(this->_outputConsole, tr("Output"));

    this->setWidget(tabWidget);
}

void DockMessage::bindMessage(MessageController *controller)
{
#ifdef DEBUG
    this->_debugConsole->bindMessage(controller);
#endif
    this->_outputConsole->bindMessage(controller);
}
