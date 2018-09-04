#ifndef SETTINGSHEATINGBEDSCREEN_H
#define SETTINGSHEATINGBEDSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsHeatingBedScreen;
}

class SettingsHeatingBedScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsHeatingBedScreen(QWidget *parent = 0);
    ~SettingsHeatingBedScreen();

private:
    Ui::SettingsHeatingBedScreen *ui;
};

#endif // SETTINGSHEATINGBEDSCREEN_H
