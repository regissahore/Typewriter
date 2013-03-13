#include "VCMainWindow.h"
#include "ui_VCMainWindow.h"

/**
 * 构造函数，初始化界面。
 * @param parent 父窗体。
 */
VCMainWindow::VCMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VCMainWindow)
{
    this->ui->setupUi(this);
    this->initDockWidget();
    this->initCentralWidget();
}

/**
 * 析构函数。
 */
VCMainWindow::~VCMainWindow()
{
    this->clearCentralWidget();
    this->clearDockWidget();
    delete this->ui;
}

/**
 * 当菜单项“关闭”被点击时触发，关闭现在的程序。
 */
void VCMainWindow::on_actionClose_triggered()
{
    this->close();
}

/**
 * 初始化各个停靠栏。
 */
void VCMainWindow::initDockWidget(void)
{
    this->dockConsole = new VCDockConsole(this);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->dockConsole);
    this->dockParameter = new VCDockParameter(this);
    this->addDockWidget(Qt::RightDockWidgetArea, this->dockParameter);
    this->dockProject = new VCDockProject(this);
    this->addDockWidget(Qt::RightDockWidgetArea, this->dockProject);
    this->dockTool = new VCDockTool(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, this->dockTool);
}

/**
 * 删除各个停靠栏。
 */
void VCMainWindow::clearDockWidget(void)
{
    if (this->dockConsole)
    {
        delete this->dockConsole;
        this->dockConsole = 0L;
    }
    if (this->dockParameter)
    {
        delete this->dockParameter;
        this->dockParameter = 0L;
    }
    if (this->dockProject)
    {
        delete this->dockProject;
        this->dockProject = 0L;
    }
    if (this->dockTool)
    {
        delete this->dockTool;
        this->dockTool = 0L;
    }
}

/**
 * 初始化编辑器。
 */
void VCMainWindow::initCentralWidget(void)
{
    this->editor = new VCWidgetEditor(this);
    this->setCentralWidget(this->editor);
}

/**
 * 删除编辑器。
 */
void VCMainWindow::clearCentralWidget(void)
{
    if (this->editor)
    {
        delete this->editor;
        this->editor = 0L;
    }
}
