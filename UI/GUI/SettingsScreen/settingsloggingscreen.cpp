#include "settingsloggingscreen.h"
#include "ui_settingsloggingscreen.h"

SettingsLoggingScreen::SettingsLoggingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsLoggingScreen)
{
    ui->setupUi(this);
}

SettingsLoggingScreen::~SettingsLoggingScreen()
{
    delete ui;
}
