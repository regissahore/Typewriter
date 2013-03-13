#ifndef VCDOCKPARAMETER_H
#define VCDOCKPARAMETER_H

#include <QDockWidget>

namespace Ui {
class VCDockParameter;
}

class VCDockParameter : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCDockParameter(QWidget *parent = 0);
    ~VCDockParameter();
    
private:
    Ui::VCDockParameter *ui;
};

#endif // VCDOCKPARAMETER_H
