#ifndef MAINMENUABSTRACT_H
#define MAINMENUABSTRACT_H
/**
 * The abstract sub main menu.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMenuBar>
#include "messager.h"

class MainMenuAbstract : public QMenu, public Messager
{
    Q_OBJECT
public:
    MainMenuAbstract();
    void bindMessage(MessageController *controller);
};

#endif // MAINMENUABSTRACT_H
