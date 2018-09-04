#include "settingsiomiscscreen.h"
#include "ui_settingsiomiscscreen.h"

SettingsIOMiscScreen::SettingsIOMiscScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsIOMiscScreen)
{
    ui->setupUi(this);
}

SettingsIOMiscScreen::~SettingsIOMiscScreen()
{
    delete ui;
}
