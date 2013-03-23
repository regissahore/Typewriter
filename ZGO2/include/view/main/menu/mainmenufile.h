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

private:
    QAction *_actionNew;
    QAction *_actionClose;
    QAction *_actionCloseAll;
    QAction *_actionSave;
    QAction *_actionSaveAs;
    QAction *_actionSaveAll;
    QAction *_actionQuit;

private slots:
    void slotActionNew();
    void slotActionClose();
    void slotActionCloseAll();
    void slotActionSave();
    void slotActionSaveAs();
    void slotActionSaveAll();
    void slotActionQuit();
};

#endif // MAINMENUFILE_H
