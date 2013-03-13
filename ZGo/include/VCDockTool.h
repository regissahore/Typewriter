#ifndef VCDOCKTOOL_H
#define VCDOCKTOOL_H

#include <QDockWidget>

namespace Ui {
class VCDockTool;
}

class VCDockTool : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCDockTool(QWidget *parent = 0);
    ~VCDockTool();
    
private:
    Ui::VCDockTool *ui;
};

#endif // VCDOCKTOOL_H
