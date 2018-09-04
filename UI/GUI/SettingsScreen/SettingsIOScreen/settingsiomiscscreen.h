#ifndef SETTINGSIOMISCSCREEN_H
#define SETTINGSIOMISCSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsIOMiscScreen;
}

class SettingsIOMiscScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsIOMiscScreen(QWidget *parent = 0);
    ~SettingsIOMiscScreen();

private:
    Ui::SettingsIOMiscScreen *ui;
};

#endif // SETTINGSIOMISCSCREEN_H
