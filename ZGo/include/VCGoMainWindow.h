#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * 程序的主窗体。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <QMainWindow>
#include "VCGoDockConsole.h"
#include "VCGoDockParameter.h"
#include "VCGoDockProject.h"
#include "VCGoDockTool.h"
#include "VCGoEditor.h"

namespace Ui {
class VCGoMainWindow;
}

class VCGoMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VCGoMainWindow(QWidget *parent = 0);
    ~VCGoMainWindow();
    
private slots:
    void on_actionClose_triggered();

private:
    Ui::VCGoMainWindow *ui; /** 窗体的界面。 */
    VCGoDockConsole *dockConsole; /** @see VCDockConsole */
    VCGoDockParameter *dockParameter; /** @see VCDockParameter */
    VCGoDockProject *dockProject; /** @see VCDockProject */
    VCGoDockTool *dockTool; /** @see VCDockTool */
    VCGoEditor *editor; /** @see VCWidgetDrawingTab */
    void initDockWidget(void);
    void clearDockWidget(void);
    void initCentralWidget(void);
    void clearCentralWidget(void);
};

#endif // MAINWINDOW_H
