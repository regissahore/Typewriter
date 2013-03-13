#ifndef VCGOEDITORTAB_H
#define VCGOEDITORTAB_H

#include <QWidget>

namespace Ui {
class VCGoEditorTab;
}

class VCGoEditorTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit VCGoEditorTab(QWidget *parent = 0);
    ~VCGoEditorTab();
    
private:
    Ui::VCGoEditorTab *ui;
};

#endif // VCGOEDITORTAB_H
