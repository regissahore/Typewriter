#include "mainmenu.h"
#include "mainmenufile.h"
#include "mainmenuanalysis.h"

/**
 * Initialize menu.
 * @param parent Parent widget.
 */
MainMenu::MainMenu(QWidget *parent) : QMenuBar(parent), Messager()
{
    this->_menuFile = new MainMenuFile();
    this->addMenu(this->_menuFile);
    this->_menuAnalysis = new MainMenuAnalysis();
    this->addMenu(this->_menuAnalysis);
}

void MainMenu::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    this->_menuFile->bindMessage(controller);
    this->_menuAnalysis->bindMessage(controller);
}

