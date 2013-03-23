#include "mainmenufile.h"
#include "messagefactory.h"

MainMenuFile::MainMenuFile() : MainMenuAbstract()
{
    this->setTitle(tr("File(&F)"));
    this->_actionClose = this->addAction(tr("Close"));
    this->connect(this->_actionClose, SIGNAL(triggered()), this, SLOT(slotActionQuit()));
}

/**
 * Try close the window.
 */
void MainMenuFile::slotActionQuit()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE));
}
