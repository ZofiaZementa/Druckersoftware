#include "settingsheatingbedscreen.h"
#include "ui_settingsheatingbedscreen.h"

SettingsHeatingBedScreen::SettingsHeatingBedScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsHeatingBedScreen)
{
    ui->setupUi(this);
}

SettingsHeatingBedScreen::~SettingsHeatingBedScreen()
{
    delete ui;
}
