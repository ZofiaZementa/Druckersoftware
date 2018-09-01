#include "infoioanaloginscreen.h"
#include "ui_infoioanaloginscreen.h"

InfoIOAnalogInScreen::InfoIOAnalogInScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOAnalogInScreen)
{
    ui->setupUi(this);
}

InfoIOAnalogInScreen::~InfoIOAnalogInScreen()
{
    delete ui;
}
