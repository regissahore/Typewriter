#ifndef VCWIDGETDRAWING_H
#define VCWIDGETDRAWING_H

#include <QWidget>

namespace Ui {
class VCWidgetDrawing;
}

class VCWidgetDrawing : public QWidget
{
    Q_OBJECT
    
public:
    explicit VCWidgetDrawing(QWidget *parent = 0);
    ~VCWidgetDrawing();
    
private:
    Ui::VCWidgetDrawing *ui;
};

#endif // VCWIDGETDRAWING_H
