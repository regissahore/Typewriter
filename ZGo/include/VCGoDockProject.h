#ifndef VCGODOCKPROJECT_H
#define VCGODOCKPROJECT_H

#include <QDockWidget>

namespace Ui {
class VCGoDockProject;
}

class VCGoDockProject : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCGoDockProject(QWidget *parent = 0);
    ~VCGoDockProject();
    
private:
    Ui::VCGoDockProject *ui;
};

#endif // VCGODOCKPROJECT_H
