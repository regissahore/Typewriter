#ifndef MAINMENU_H
#define MAINMENU_H
/**
 * 主菜单。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMenuBar>
#include "messager.h"

class MainMenuFile;
class MainMenuAnalysis;

class MainMenu : public QMenuBar, public Messager
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

private:
    MainMenuFile *_menuFile;
    MainMenuAnalysis *_menuAnalysis;
};

#endif // MAINMENU_H
