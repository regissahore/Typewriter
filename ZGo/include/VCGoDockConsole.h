#ifndef VCGODOCKCONSOLE_H
#define VCGODOCKCONSOLE_H

#include <QDockWidget>

namespace Ui {
class VCGoDockConsole;
}

class VCGoDockConsole : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit VCGoDockConsole(QWidget *parent = 0);
    ~VCGoDockConsole();
    
private:
    Ui::VCGoDockConsole *ui;
};

#endif // VCGODOCKCONSOLE_H
