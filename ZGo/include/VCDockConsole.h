#ifndef VCDOCKCONSOLE_H
#define VCDOCKCONSOLE_H

#include <QDockWidget>

namespace Ui {
class VCDockConsole;
}

class VCDockConsole : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCDockConsole(QWidget *parent = 0);
    ~VCDockConsole();
    
private:
    Ui::VCDockConsole *ui;
};

#endif // VCDOCKCONSOLE_H
