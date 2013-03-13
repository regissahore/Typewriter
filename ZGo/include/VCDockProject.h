#ifndef VCDOCKPROJECT_H
#define VCDOCKPROJECT_H

#include <QDockWidget>

namespace Ui {
class VCDockProject;
}

class VCDockProject : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCDockProject(QWidget *parent = 0);
    ~VCDockProject();
    
private:
    Ui::VCDockProject *ui;
};

#endif // VCDOCKPROJECT_H
