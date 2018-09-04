#include "settingsguispinboxscreen.h"
#include "ui_settingsguispinboxscreen.h"

SettingsGUISpinBoxScreen::SettingsGUISpinBoxScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGUISpinBoxScreen)
{
    ui->setupUi(this);
}

SettingsGUISpinBoxScreen::~SettingsGUISpinBoxScreen()
{
    delete ui;
}
