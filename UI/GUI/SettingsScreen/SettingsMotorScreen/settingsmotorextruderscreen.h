#ifndef SETTINGSMOTOREXTRUDERSCREEN_H
#define SETTINGSMOTOREXTRUDERSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsMotorExtruderScreen;
}

class SettingsMotorExtruderScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorExtruderScreen(QWidget *parent = 0);
    ~SettingsMotorExtruderScreen();

private:
    Ui::SettingsMotorExtruderScreen *ui;
};

#endif // SETTINGSMOTOREXTRUDERSCREEN_H
