#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * 程序的主窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMainWindow>
#include "controller/messager.h"
#include "controller/messagefactorymainwindow.h"
#include "view/editor.h"
#include "view/dockmessage.h"

class MainWindow : public QMainWindow, public Messager
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bindMessage();
    void bindMessage(MessageController *controller);

private:
    MessageController *_messageController; /** 程序唯一的实例化的消息控制器。 */
    Editor *_editor; /** GO法的编辑器。 */
    DockMessage *_dockMessage; /** 消息悬停窗口。 */
    void initEditor();
    void clearEditor();
    void initDock();
    void clearDock();
    
signals:

    
};

#endif // MAINWINDOW_H
