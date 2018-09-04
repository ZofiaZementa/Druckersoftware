#include "settingsgeneralscreen.h"
#include "ui_settingsgeneralscreen.h"

SettingsGeneralScreen::SettingsGeneralScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGeneralScreen)
{
    ui->setupUi(this);
}

SettingsGeneralScreen::~SettingsGeneralScreen()
{
    delete ui;
}
