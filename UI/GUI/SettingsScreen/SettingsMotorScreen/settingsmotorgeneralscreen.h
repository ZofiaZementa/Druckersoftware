#ifndef SETTINGSMOTORGENERALSCREEN_H
#define SETTINGSMOTORGENERALSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsMotorGeneralScreen;
}

class SettingsMotorGeneralScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorGeneralScreen(QWidget *parent = 0);
    ~SettingsMotorGeneralScreen();

private:
    Ui::SettingsMotorGeneralScreen *ui;
};

#endif // SETTINGSMOTORGENERALSCREEN_H
