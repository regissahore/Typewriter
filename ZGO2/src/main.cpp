#include <QDir>
#include <QString>
#include <QTranslator>
#include <QApplication>
#include "gomainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QTranslator translator;
    translator.load("lang/Lang_CH.qm");
    application.installTranslator(&translator);
    GOMainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
