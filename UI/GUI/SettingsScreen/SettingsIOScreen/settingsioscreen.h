#ifndef SETTINGSIOSCREEN_H
#define SETTINGSIOSCREEN_H

#include <QWidget>
#include "UI/GUI/SettingsScreen/SettingsIOScreen/settingsiosensorscreen.h"
#include "UI/GUI/SettingsScreen/SettingsIOScreen/settingsioheatingscreen.h"
#include "UI/GUI/SettingsScreen/SettingsIOScreen/settingsiolightingscreen.h"
#include "UI/GUI/SettingsScreen/SettingsIOScreen/settingsiomiscscreen.h"

namespace Ui {
class SettingsIOScreen;
}

class SettingsIOScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsIOScreen(QWidget *parent = 0);
    ~SettingsIOScreen();

private slots:

    void sensorButtonClicked();
    void heatingButtonClicked();
    void lightingButtonClicked();
    void miscButtonClicked();

private:

    Ui::SettingsIOScreen *ui;
    SettingsIOSensorScreen *m_settingsIOSensorScreen;
    SettingsIOHeatingScreen *m_settingsIOHeatingScreen;
    SettingsIOLightingScreen *m_settingsIOLightingScreen;
    SettingsIOMiscScreen *m_settingsIOMiscScreen;
};

#endif // SETTINGSIOSCREEN_H
