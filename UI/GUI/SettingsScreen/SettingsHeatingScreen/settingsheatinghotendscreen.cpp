#include "settingsheatinghotendscreen.h"
#include "ui_settingsheatinghotendscreen.h"

SettingsHeatingHotEndScreen::SettingsHeatingHotEndScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsHeatingHotEndScreen)
{
    ui->setupUi(this);
}

SettingsHeatingHotEndScreen::~SettingsHeatingHotEndScreen()
{
    delete ui;
}
