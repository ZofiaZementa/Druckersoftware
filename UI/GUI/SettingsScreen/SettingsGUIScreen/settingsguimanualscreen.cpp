#include "settingsguimanualscreen.h"
#include "ui_settingsguimanualscreen.h"

SettingsGUIManualScreen::SettingsGUIManualScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGUIManualScreen)
{
    ui->setupUi(this);
}

SettingsGUIManualScreen::~SettingsGUIManualScreen()
{
    delete ui;
}
