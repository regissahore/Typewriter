#include <QtGui/QApplication>
#include "VCMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VCMainWindow w;
    w.show();
    
    return a.exec();
}
