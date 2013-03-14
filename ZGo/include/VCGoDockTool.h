#ifndef VCGODOCKTOOL_H
#define VCGODOCKTOOL_H

#include <QDockWidget>

namespace Ui {
class VCGoDockTool;
}

class VCGoDockTool : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCGoDockTool(QWidget *parent = 0);
    ~VCGoDockTool();
    
private:
    Ui::VCGoDockTool *ui;
};

#endif // VCGODOCKTOOL_H
