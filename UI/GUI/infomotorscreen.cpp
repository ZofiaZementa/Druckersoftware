#include "infomotorscreen.h"
#include "ui_infomotorscreen.h"

InfoMotorScreen::InfoMotorScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoMotorScreen)
{
    ui->setupUi(this);
}

InfoMotorScreen::~InfoMotorScreen()
{
    delete ui;
}
