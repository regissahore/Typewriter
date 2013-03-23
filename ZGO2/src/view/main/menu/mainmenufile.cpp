#include "mainmenufile.h"
#include "messagefactory.h"

MainMenuFile::MainMenuFile() : MainMenuAbstract()
{
    this->setTitle(tr("File(&F)"));
    this->_actionNew = this->addAction(tr("New(&N)"));
    this->_actionClose = this->addAction(tr("Close(&C)"));
    this->_actionCloseAll = this->addAction(tr("Close All"));
    this->addSeparator();
    this->_actionSave = this->addAction(tr("Save(&S)"));
    this->_actionSaveAs = this->addAction(tr("Save As..."));
    this->_actionSaveAll = this->addAction(tr("Save All"));
    this->addSeparator();
    this->_actionQuit = this->addAction(tr("Quit(&Q)"));
    this->_actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    this->_actionClose->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    this->_actionCloseAll->setShortcut(QKeySequence(Qt::SHIFT + Qt::CTRL + Qt::Key_W));
    this->_actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    this->_actionSaveAll->setShortcut(QKeySequence(Qt::SHIFT + Qt::CTRL + Qt::Key_S));
    this->_actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    this->connect(this->_actionNew, SIGNAL(triggered()), this, SLOT(slotActionNew()));
    this->connect(this->_actionClose, SIGNAL(triggered()), this, SLOT(slotActionClose()));
    this->connect(this->_actionCloseAll, SIGNAL(triggered()), this, SLOT(slotActionCloseAll()));
    this->connect(this->_actionSave, SIGNAL(triggered()), this, SLOT(slotActionSave()));
    this->connect(this->_actionSaveAs, SIGNAL(triggered()), this, SLOT(slotActionSaveAs()));
    this->connect(this->_actionSaveAll, SIGNAL(triggered()), this, SLOT(slotActionSaveAll()));
    this->connect(this->_actionQuit, SIGNAL(triggered()), this, SLOT(slotActionQuit()));
}

void MainMenuFile::slotActionNew()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_NEW));
}

void MainMenuFile::slotActionClose()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSE));
}

void MainMenuFile::slotActionCloseAll()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_CLOSEALL));
}

void MainMenuFile::slotActionSave()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVE));
}

void MainMenuFile::slotActionSaveAs()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEAS));
}

void MainMenuFile::slotActionSaveAll()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_SAVEALL));
}

void MainMenuFile::slotActionQuit()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_MAINWINDOW_TRYCLOSE));
}
