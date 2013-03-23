#ifndef MAINMENU_H
#define MAINMENU_H
/**
 * 主菜单。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include "messager.h"
#include "mainmenufile.h"

class MainMenu : public QMenuBar, public Messager
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

private:
    MainMenuFile *_menuFile;
};

#endif // MAINMENU_H
