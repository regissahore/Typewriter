#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * 程序的主窗体。
 * @author ZHG <CyberZHG@gmail.com>
 */

#include <QMainWindow>
#include "VCDockConsole.h"
#include "VCDockParameter.h"
#include "VCDockProject.h"
#include "VCDockTool.h"
#include "VCWidgetEditor.h"

namespace Ui {
class VCMainWindow;
}

class VCMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VCMainWindow(QWidget *parent = 0);
    ~VCMainWindow();
    
private slots:
    void on_actionClose_triggered();

private:
    Ui::VCMainWindow *ui; /** 窗体的界面。 */
    VCDockConsole *dockConsole; /** @see VCDockConsole */
    VCDockParameter *dockParameter; /** @see VCDockParameter */
    VCDockProject *dockProject; /** @see VCDockProject */
    VCDockTool *dockTool; /** @see VCDockTool */
    VCWidgetEditor *editor; /** @see VCWidgetDrawingTab */
    void initDockWidget(void);
    void clearDockWidget(void);
    void initCentralWidget(void);
    void clearCentralWidget(void);
};

#endif // MAINWINDOW_H
