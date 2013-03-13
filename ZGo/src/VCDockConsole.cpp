#include "include/VCDockConsole.h"
#include "ui_VCDockConsole.h"

VCDockConsole::VCDockConsole(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCDockConsole)
{
    ui->setupUi(this);
}

VCDockConsole::~VCDockConsole()
{
    delete ui;
}
