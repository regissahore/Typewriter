#include <QDir>
#include <QFont>
#include <QString>
#include <QTranslator>
#include <QApplication>
#include <QFontDatabase>
#include "gomainwindow.h"

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
    QApplication application(argc, argv);
    QTranslator translator;
    translator.load("lang/Lang_CH.qm");
    application.installTranslator(&translator);
    bindFont(application);
    GOMainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
