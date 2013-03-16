#ifndef MAINMENU_H
#define MAINMENU_H
/**
 * 主菜单。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include "controller/messager.h"
#include "controller/messagefactorymainwindow.h"

class MainMenu : public QMenuBar, public Messager
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    void bindMessage(MessageController *controller);

private:
    QMenu *_menuFile;
    QAction *_actionClose;
    QMenu *_menuHelp;

private slots:
    void slotActionClose();
};

#endif // MAINMENU_H
