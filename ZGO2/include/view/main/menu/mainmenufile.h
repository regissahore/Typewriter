#ifndef MAINMENUFILE_H
#define MAINMENUFILE_H
/**
 * The main menu of file.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMenu>
#include "mainmenuabstract.h"

class MainMenuFile : public MainMenuAbstract
{
    Q_OBJECT
public:
    MainMenuFile();
    void initMenu(QMenuBar *menuBar);

private:
    QAction *_actionNew;
    QAction *_actionClose;
    QAction *_actionCloseAll;
    QAction *_actionSave;
    QAction *_actionSaveAs;
    QAction *_actionSaveAll;
    QAction *_actionQuit;

private slots:
    void slotActionQuit();
};

#endif // MAINMENUFILE_H
