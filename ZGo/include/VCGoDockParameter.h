#ifndef VCGODOCKPARAMETER_H
#define VCGODOCKPARAMETER_H

#include <QDockWidget>

namespace Ui {
class VCGoDockParameter;
}

class VCGoDockParameter : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCGoDockParameter(QWidget *parent = 0);
    ~VCGoDockParameter();
    
private:
    Ui::VCGoDockParameter *ui;
};

#endif // VCGODOCKPARAMETER_H
