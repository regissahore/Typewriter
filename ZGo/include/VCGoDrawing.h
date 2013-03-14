#ifndef VCGODRAWING_H
#define VCGODRAWING_H

#include <QWidget>

namespace Ui {
class VCGoDrawing;
}

class VCGoDrawing : public QWidget
{
    Q_OBJECT
    
public:
    explicit VCGoDrawing(QWidget *parent = 0);
    ~VCGoDrawing();
    
private:
    Ui::VCGoDrawing *ui;
};

#endif // VCGODRAWING_H
