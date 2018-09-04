#include "settingsioheatingscreen.h"
#include "ui_settingsioheatingscreen.h"

SettingsIOHeatingScreen::SettingsIOHeatingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsIOHeatingScreen)
{
    ui->setupUi(this);
}

SettingsIOHeatingScreen::~SettingsIOHeatingScreen()
{
    delete ui;
}
