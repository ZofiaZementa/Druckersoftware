#include "infoioanalogscreen.h"
#include "ui_infoioanalogscreen.h"

InfoIOAnalogScreen::InfoIOAnalogScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOAnalogScreen)
{
    ui->setupUi(this);
}

InfoIOAnalogScreen::~InfoIOAnalogScreen()
{
    delete ui;
}
