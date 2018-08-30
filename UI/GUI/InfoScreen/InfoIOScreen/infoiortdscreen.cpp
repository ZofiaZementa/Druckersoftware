#include "infoiortdscreen.h"
#include "ui_infoiortdscreen.h"

InfoIORTDScreen::InfoIORTDScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIORTDScreen)
{
    ui->setupUi(this);
}

InfoIORTDScreen::~InfoIORTDScreen()
{
    delete ui;
}
