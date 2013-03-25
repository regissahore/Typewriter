#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * 程序的主窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QSettings>
#include <QMainWindow>
#include "messager.h"
#include "mainmenu.h"
#include "editor.h"
#include "dockmessage.h"
#include "docktoolbox.h"
#include "dockparameter.h"

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
    DockToolbox *_dockToolbox; /** 工具箱悬停窗口。 */
    DockParameter *_dockParameter; /** The parameter dock widget. */
    void initEditor();
    void initDock();
    void initMenu();
    
signals:

    
};

#endif // MAINWINDOW_H
