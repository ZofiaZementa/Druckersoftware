#ifndef SETTINGSMOTORYAXISSCREEN_H
#define SETTINGSMOTORYAXISSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsMotorYAxisScreen;
}

class SettingsMotorYAxisScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorYAxisScreen(QWidget *parent = 0);
    ~SettingsMotorYAxisScreen();

private:
    Ui::SettingsMotorYAxisScreen *ui;
};

#endif // SETTINGSMOTORYAXISSCREEN_H
