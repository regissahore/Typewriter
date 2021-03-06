#include <cstdio>
#include <QDir>
#include <QFont>
#include <QString>
#include <QTranslator>
#include <QApplication>
#include <QFontDatabase>
#include "GoMainWindow.h"

void bindFont(QApplication &application)
{
    int fontId = QFontDatabase::addApplicationFont("font/default.ttf");
    QStringList fontFamily = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamily.empty())
    {
        QFont font(fontFamily.at(0), 9);
        font.setStyleStrategy(QFont::PreferAntialias);
        application.setFont(font);
    }
}

int main(int argc, char *argv[])
{
    freopen("stdout.log", "a", stdout);
    freopen("stderr.log", "a", stderr);
    QApplication application(argc, argv);
    QTranslator translator;
    translator.load("lang/Lang_CH.qm");
    application.installTranslator(&translator);
    bindFont(application);
    GoMainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
