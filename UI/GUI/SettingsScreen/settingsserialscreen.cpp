#include "settingsserialscreen.h"
#include "ui_settingsserialscreen.h"

SettingsSerialScreen::SettingsSerialScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsSerialScreen)
{
    ui->setupUi(this);
}

SettingsSerialScreen::~SettingsSerialScreen()
{
    delete ui;
}
