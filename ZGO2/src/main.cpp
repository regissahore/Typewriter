#include <QTranslator>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QTranslator translator;
    translator.load("Lang_CH.qm");
    application.installTranslator(&translator);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
