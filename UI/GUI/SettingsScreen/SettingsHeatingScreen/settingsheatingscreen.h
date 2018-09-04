#ifndef SETTINGSHEATINGSCREEN_H
#define SETTINGSHEATINGSCREEN_H

#include <QWidget>
#include "UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatinghotendscreen.h"
#include "UI/GUI/SettingsScreen/SettingsHeatingScreen/settingsheatingbedscreen.h"

namespace Ui {
class SettingsHeatingScreen;
}

class SettingsHeatingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsHeatingScreen(QWidget *parent = 0);
    ~SettingsHeatingScreen();

private slots:

    void hotEndButtonClicked();
    void bedButtonClicked();

private:

    Ui::SettingsHeatingScreen *ui;
    SettingsHeatingHotEndScreen *m_settingsHeatingHotEndScreen;
    SettingsHeatingBedScreen *m_settingsHeatingBedScreen;
};

#endif // SETTINGSHEATINGSCREEN_H
