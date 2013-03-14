#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * 程序的主窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QMainWindow>
#include "view/editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Editor *editor; /** GO法的编辑器。 */
    void initEditor();
    void clearEditor();
    
signals:

    
};

#endif // MAINWINDOW_H
