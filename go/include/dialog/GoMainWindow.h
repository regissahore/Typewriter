#ifndef GOMAINWINDOW_H
#define GOMAINWINDOW_H
#include "stable.h"
#include "Messager.h"
#include "Editor.h"
#include "DockMessage.h"
#include "DockToolbox.h"
#include "DockParameter.h"

namespace Ui {
class GoMainWindow;
}

class GoMainWindow : public QMainWindow, public Messager
{
    Q_OBJECT
public:
    explicit GoMainWindow(QWidget *parent = 0);
    ~GoMainWindow();
    void bindMessage();
    void messageEvent(QSharedPointer<Message> message);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::GoMainWindow *ui;
    bool _close;
    Editor _editor;
    DockMessage _dockMessage;
    DockParameter _dockParameter;
    DockToolbox _dockToolbox;
    void initEditor();
    void initDock();

private slots:
    void on_toolButtonNew_clicked();
    void on_toolButtonMarkov_clicked();
    void on_toolButtonOpen_clicked();
    void on_toolButtonClose_clicked();
    void on_toolButtonSave_clicked();
    void on_toolButtonSaveAs_clicked();
    void on_toolButtonSaveAll_clicked();
    void on_toolButtonAnalysis_clicked();
    void on_toolButtonPath_clicked();
    void on_toolButtonCut_clicked();
    void on_toolButtonCopy_clicked();
    void on_toolButtonDelete_clicked();
    void on_toolButtonZoomIn_clicked();
    void on_toolButtonZoomOut_clicked();
    void on_toolButtonFeedback_clicked();
    void on_toolButtonUnlockFb_clicked();
};

#endif // GOMAINWINDOW_H
