#ifndef VCGOEDITOR_H
#define VCGOEDITOR_H
/**
 * GO法的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include "VCGoEditorTab.h"

namespace Ui {
class VCGoEditor;
}

class VCGoEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit VCGoEditor(QWidget *parent = 0);
    ~VCGoEditor();
    
private slots:
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::VCGoEditor *ui; /** 界面文件。*/
};

#endif // VCGOEDITOR_H
