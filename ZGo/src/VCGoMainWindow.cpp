#include "VCGoMainWindow.h"
#include "ui_VCGoMainWindow.h"

/**
 * 构造函数，初始化界面。
 * @param parent 父窗体。
 */
VCGoMainWindow::VCGoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VCGoMainWindow)
{
    this->ui->setupUi(this);
    this->initDockWidget();
    this->initCentralWidget();
}

/**
 * 析构函数。
 */
VCGoMainWindow::~VCGoMainWindow()
{
    this->clearCentralWidget();
    this->clearDockWidget();
    delete this->ui;
}

/**
 * 当菜单项“关闭”被点击时触发，关闭现在的程序。
 */
void VCGoMainWindow::on_actionClose_triggered()
{
    this->close();
}

/**
 * 初始化各个停靠栏。
 */
void VCGoMainWindow::initDockWidget(void)
{
    this->dockConsole = new VCGoDockConsole(this);
    this->addDockWidget(Qt::BottomDockWidgetArea, this->dockConsole);
    this->dockParameter = new VCGoDockParameter(this);
    this->addDockWidget(Qt::RightDockWidgetArea, this->dockParameter);
    this->dockProject = new VCGoDockProject(this);
    this->addDockWidget(Qt::RightDockWidgetArea, this->dockProject);
    this->dockTool = new VCGoDockTool(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, this->dockTool);
}

/**
 * 删除各个停靠栏。
 */
void VCGoMainWindow::clearDockWidget(void)
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
void VCGoMainWindow::initCentralWidget(void)
{
    this->editor = new VCGoEditor(this);
    this->setCentralWidget(this->editor);
}

/**
 * 删除编辑器。
 */
void VCGoMainWindow::clearCentralWidget(void)
{
    if (this->editor)
    {
        delete this->editor;
        this->editor = 0L;
    }
}
