#include "settingsmotorgeneralscreen.h"
#include "ui_settingsmotorgeneralscreen.h"

SettingsMotorGeneralScreen::SettingsMotorGeneralScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorGeneralScreen)
{
    ui->setupUi(this);
}

SettingsMotorGeneralScreen::~SettingsMotorGeneralScreen()
{
    delete ui;
}
