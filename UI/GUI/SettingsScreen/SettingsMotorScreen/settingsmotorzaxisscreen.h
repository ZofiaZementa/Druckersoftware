#ifndef SETTINGSMOTORZAXISSCREEN_H
#define SETTINGSMOTORZAXISSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsMotorZAxisScreen;
}

class SettingsMotorZAxisScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorZAxisScreen(QWidget *parent = 0);
    ~SettingsMotorZAxisScreen();

private:
    Ui::SettingsMotorZAxisScreen *ui;
};

#endif // SETTINGSMOTORZAXISSCREEN_H
