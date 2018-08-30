#include "infoiodigitalscreen.h"
#include "ui_infoiodigitalscreen.h"

InfoIODigitalScreen::InfoIODigitalScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIODigitalScreen)
{
    ui->setupUi(this);
}

InfoIODigitalScreen::~InfoIODigitalScreen()
{
    delete ui;
}
