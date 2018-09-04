#include "settingsmotoryaxisscreen.h"
#include "ui_settingsmotoryaxisscreen.h"

SettingsMotorYAxisScreen::SettingsMotorYAxisScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorYAxisScreen)
{
    ui->setupUi(this);
}

SettingsMotorYAxisScreen::~SettingsMotorYAxisScreen()
{
    delete ui;
}
