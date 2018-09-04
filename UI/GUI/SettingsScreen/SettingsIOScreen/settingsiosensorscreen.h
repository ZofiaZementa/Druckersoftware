#ifndef SETTINGSIOSENSORSCREEN_H
#define SETTINGSIOSENSORSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsIOSensorScreen;
}

class SettingsIOSensorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsIOSensorScreen(QWidget *parent = 0);
    ~SettingsIOSensorScreen();

private:
    Ui::SettingsIOSensorScreen *ui;
};

#endif // SETTINGSIOSENSORSCREEN_H
