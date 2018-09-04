#ifndef SETTINGSMOTORXAXISSCREEN_H
#define SETTINGSMOTORXAXISSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsMotorXAxisScreen;
}

class SettingsMotorXAxisScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorXAxisScreen(QWidget *parent = 0);
    ~SettingsMotorXAxisScreen();

private:
    Ui::SettingsMotorXAxisScreen *ui;
};

#endif // SETTINGSMOTORXAXISSCREEN_H
