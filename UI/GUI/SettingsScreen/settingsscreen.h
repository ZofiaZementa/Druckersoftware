#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include "UI/GUI/SettingsScreen/settingsgeneralscreen.h"
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorscreen.h"
#include "UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguiscreen.h"
#include "UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingscreen.h"
#include "UI/GUI/SettingsScreen/SettingsIOScreen/settingsioscreen.h"
#include "UI/GUI/SettingsScreen/settingsloggingscreen.h"
#include "UI/GUI/SettingsScreen/settingsserialscreen.h"

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = 0);
    ~SettingsScreen();

private slots:

    void generalButtonClicked();
    void motorButtonClicked();
    void guiButtonClicked();
    void heatingButtonClicked();
    void ioButonClicked();
    void loggingButtonClicked();
    void serialButtonClicked();

private:

    Ui::SettingsScreen *ui;
    SettingsGeneralScreen *m_settingsGeneralScreen;
    SettingsMotorScreen *m_settingsMotorScreen;
    SettingsGUIScreen *m_settingsGUIScreen;
    SettingsHeatingScreen *m_settingsHeatingScreen;
    SettingsIOScreen *m_settingsIOScreen;
    SettingsLoggingScreen *m_settingsLoggingScreen;
    SettingsSerialScreen *m_settingsSerialScreen;
};

#endif // SETTINGSSCREEN_H
