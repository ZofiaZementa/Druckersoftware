#include "settingsmotorzaxisscreen.h"
#include "ui_settingsmotorzaxisscreen.h"

SettingsMotorZAxisScreen::SettingsMotorZAxisScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorZAxisScreen)
{
    ui->setupUi(this);
}

SettingsMotorZAxisScreen::~SettingsMotorZAxisScreen()
{
    delete ui;
}
