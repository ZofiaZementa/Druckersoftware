#include "settingsmotorextruderscreen.h"
#include "ui_settingsmotorextruderscreen.h"

SettingsMotorExtruderScreen::SettingsMotorExtruderScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorExtruderScreen)
{
    ui->setupUi(this);
}

SettingsMotorExtruderScreen::~SettingsMotorExtruderScreen()
{
    delete ui;
}
