#include "mainmenuanalysis.h"
#include "messagefactory.h"

MainMenuAnalysis::MainMenuAnalysis()
{
    this->setTitle(tr("Analysis(&A)"));
    this->_actionStart = this->addAction(tr("Start"));
    this->_actionStart->setShortcut(QKeySequence(Qt::Key_F9));
    this->connect(this->_actionStart, SIGNAL(triggered()), this, SLOT(slotActionStart()));
}

void MainMenuAnalysis::slotActionStart()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS));
}
