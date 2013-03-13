#ifndef VCWIDGETEDITOR_H
#define VCWIDGETEDITOR_H
/**
 * GO法的编辑器。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QWidget>
#include "VCGoEditorTab.h"

namespace Ui {
class VCWidgetEditor;
}

class VCWidgetEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit VCWidgetEditor(QWidget *parent = 0);
    ~VCWidgetEditor();
    
private:
    Ui::VCWidgetEditor *ui;
};

#endif // VCWIDGETEDITOR_H
