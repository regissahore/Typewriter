#include "mainmenuabstract.h"

MainMenuAbstract::MainMenuAbstract() : QMenu(), Messager()
{
}

void MainMenuAbstract::bindMessage(MessageController *controller)
{
    this->Messager::bindMessage(controller);
}
