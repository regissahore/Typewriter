#include <QtGui/QApplication>
#include "VCGoMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VCGoMainWindow w;
    w.show();
    
    return a.exec();
}
