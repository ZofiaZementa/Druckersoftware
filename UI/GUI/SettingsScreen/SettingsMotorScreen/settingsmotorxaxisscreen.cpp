#include "settingsmotorxaxisscreen.h"
#include "ui_settingsmotorxaxisscreen.h"

SettingsMotorXAxisScreen::SettingsMotorXAxisScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorXAxisScreen)
{
    ui->setupUi(this);
}

SettingsMotorXAxisScreen::~SettingsMotorXAxisScreen()
{
    delete ui;
}
