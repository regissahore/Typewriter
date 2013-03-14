#include "view/mainwindow.h"

/**
 * 构造函数，初始化界面。
 * @param parent 父窗体。
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(tr("ZHG GO Analysis"));
    this->setGeometry(0, 0, 800, 600);
    this->initEditor();
}

/**
 * 析构函数，清除界面资源。
 */
MainWindow::~MainWindow()
{
    this->clearEditor();
}

/**
 * 初始化编辑器。
 */
void MainWindow::initEditor()
{
    this->editor = new Editor(this);
    this->setCentralWidget(this->editor);
}

/**
 * 清楚编辑器。
 * @return
 */
void MainWindow::clearEditor()
{
    if (this->editor)
    {
        delete this->editor;
        this->editor = 0;
    }
}
