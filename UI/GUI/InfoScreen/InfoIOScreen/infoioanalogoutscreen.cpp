#include "infoioanalogoutscreen.h"
#include "ui_infoioanalogoutscreen.h"

InfoIOAnalogOutScreen::InfoIOAnalogOutScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOAnalogOutScreen)
{
    ui->setupUi(this);
}

InfoIOAnalogOutScreen::~InfoIOAnalogOutScreen()
{
    delete ui;
}
