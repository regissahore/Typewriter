#ifndef GOMAINWINDOW_H
#define GOMAINWINDOW_H
/**
 * 程序的主窗口。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QSettings>
#include <QMainWindow>
#include "messager.h"
#include "editor.h"
#include "dockmessage.h"
#include "docktoolbox.h"
#include "dockparameter.h"

namespace Ui {
class GOMainWindow;
}

class GOMainWindow : public QMainWindow, public Messager
{
    Q_OBJECT
public:
    explicit GOMainWindow(QWidget *parent = 0);
    ~GOMainWindow();
    void bindMessage(MessageController *controller);
    void messageEvent(Message *message);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::GOMainWindow *ui;
    bool _close; /** 当该值为true时才能关闭程序。 */
    MessageController *_messageController; /** 程序唯一的实例化的消息控制器。 */
    Editor *_editor; /** GO法的编辑器。 */
    DockMessage *_dockMessage; /** 消息悬停窗口。 */
    DockToolbox *_dockToolbox; /** 工具箱悬停窗口。 */
    DockParameter *_dockParameter; /** The parameter dock widget. */
    void initEditor();
    void initDock();
    void initToolBar();

private slots:
    void on_actionNew_triggered();
    void on_actionNew_Markov_triggered();
    void on_actionOpen_O_triggered();
    void on_actionClose_C_triggered();
    void on_actionClose_All_triggered();
    void on_actionSave_S_triggered();
    void on_actionSave_As_triggered();
    void on_actionSave_All_triggered();
    void on_actionQuit_Q_triggered();
    void on_actionAnalysis_Probability_triggered();
    void on_actionFind_Path_triggered();
    void on_actionFind_Cut_triggered();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void on_actionTool_DockWidget_toggled(bool value);
    void on_actionParameter_DockWidget_toggled(bool value);
    void on_actionMessage_DockWidget_toggled(bool value);
    void on_actionFile_Toolbar_toggled(bool value);
    void on_actionAnalysis_Toolbar_toggled(bool value);
    void on_actionCopy_C_triggered();
    void on_actionDelete_D_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSet_Global_Feedback_triggered();
    void on_actionUnset_Global_Feedback_triggered();
    void on_actionShow_Parameter_triggered();
    void on_actionHide_Parameter_triggered();
};

#endif // GOMAINWINDOW_H
