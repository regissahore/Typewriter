#include "mainmenuanalysis.h"
#include "messagefactory.h"

MainMenuAnalysis::MainMenuAnalysis()
{
    this->setTitle(tr("Analysis(&A)"));
    this->_actionProbability = this->addAction(tr("Analysis Probability"));
    this->_actionPath = this->addAction(tr("Find Path Set"));
    this->_actionCut = this->addAction(tr("Find Cut Set"));
    this->_actionProbability->setShortcut(QKeySequence(Qt::Key_F9));
    this->connect(this->_actionProbability, SIGNAL(triggered()), this, SLOT(slotActionProbability()));
    this->connect(this->_actionPath, SIGNAL(triggered()), this, SLOT(slotActionPath()));
    this->connect(this->_actionCut, SIGNAL(triggered()), this, SLOT(slotActionCut()));
}

void MainMenuAnalysis::slotActionProbability()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PROBABILITY));
}

void MainMenuAnalysis::slotActionPath()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_PATH));
}

void MainMenuAnalysis::slotActionCut()
{
    this->sendMessage(MessageFactory::produce(MessageFactory::TYPE_EDITOR_ANALYSIS_CUT));
}
