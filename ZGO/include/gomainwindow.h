#ifndef GOMAINWINDOW_H
#define GOMAINWINDOW_H
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
    void messageEvent(QSharedPointer<Message> message);

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
