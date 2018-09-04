#include "settingsiosensorscreen.h"
#include "ui_settingsiosensorscreen.h"

SettingsIOSensorScreen::SettingsIOSensorScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsIOSensorScreen)
{
    ui->setupUi(this);
}

SettingsIOSensorScreen::~SettingsIOSensorScreen()
{
    delete ui;
}
