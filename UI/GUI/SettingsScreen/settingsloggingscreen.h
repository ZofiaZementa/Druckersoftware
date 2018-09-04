#ifndef SETTINGSLOGGINGSCREEN_H
#define SETTINGSLOGGINGSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsLoggingScreen;
}

class SettingsLoggingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsLoggingScreen(QWidget *parent = 0);
    ~SettingsLoggingScreen();

private:
    Ui::SettingsLoggingScreen *ui;
};

#endif // SETTINGSLOGGINGSCREEN_H
