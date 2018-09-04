#ifndef SETTINGSIOHEATINGSCREEN_H
#define SETTINGSIOHEATINGSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsIOHeatingScreen;
}

class SettingsIOHeatingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsIOHeatingScreen(QWidget *parent = 0);
    ~SettingsIOHeatingScreen();

private:
    Ui::SettingsIOHeatingScreen *ui;
};

#endif // SETTINGSIOHEATINGSCREEN_H
