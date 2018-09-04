#ifndef SETTINGSIOLIGHTINGSCREEN_H
#define SETTINGSIOLIGHTINGSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsIOLightingScreen;
}

class SettingsIOLightingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsIOLightingScreen(QWidget *parent = 0);
    ~SettingsIOLightingScreen();

private:
    Ui::SettingsIOLightingScreen *ui;
};

#endif // SETTINGSIOLIGHTINGSCREEN_H
