#include "mainmenu.h"

/**
 * Initialize menu.
 * @param parent Parent widget.
 */
MainMenu::MainMenu(QWidget *parent) : QMenuBar(parent), Messager()
{
    this->_menuFile = new MainMenuFile();
    this->addMenu(this->_menuFile);
}

void MainMenu::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
    this->_menuFile->bindMessage(controller);
}

