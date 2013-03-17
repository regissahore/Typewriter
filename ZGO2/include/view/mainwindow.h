#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * 程序的主窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QSettings>
#include <QMainWindow>
#include "controller/messager.h"
#include "controller/messagefactorymainwindow.h"
#include "view/mainmenu.h"
#include "view/editor.h"
#include "view/dockmessage.h"

class MainWindow : public QMainWindow, public Messager
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    void closeEvent(QCloseEvent *event);

private:
    bool _close; /** 当该值为true时才能关闭程序。 */
    MessageController *_messageController; /** 程序唯一的实例化的消息控制器。 */
    MainMenu *_mainMenu; /** 主菜单。 */
    Editor *_editor; /** GO法的编辑器。 */
    DockMessage *_dockMessage; /** 消息悬停窗口。 */
    void initEditor();
    void clearEditor();
    void initDock();
    void clearDock();
    void initMenu();
    void clearMenu();
    
signals:

    
};

#endif // MAINWINDOW_H
