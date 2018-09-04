#include "settingsiolightingscreen.h"
#include "ui_settingsiolightingscreen.h"

SettingsIOLightingScreen::SettingsIOLightingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsIOLightingScreen)
{
    ui->setupUi(this);
}

SettingsIOLightingScreen::~SettingsIOLightingScreen()
{
    delete ui;
}
