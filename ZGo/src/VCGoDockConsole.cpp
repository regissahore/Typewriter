#include "VCGoDockConsole.h"
#include "ui_VCGoDockConsole.h"

VCGoDockConsole::VCGoDockConsole(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VCGoDockConsole)
{
    ui->setupUi(this);
}

VCGoDockConsole::~VCGoDockConsole()
{
    delete ui;
}
