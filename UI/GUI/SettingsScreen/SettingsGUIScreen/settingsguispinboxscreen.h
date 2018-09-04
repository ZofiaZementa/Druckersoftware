#ifndef SETTINGSGUISPINBOXSCREEN_H
#define SETTINGSGUISPINBOXSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsGUISpinBoxScreen;
}

class SettingsGUISpinBoxScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsGUISpinBoxScreen(QWidget *parent = 0);
    ~SettingsGUISpinBoxScreen();

private:

    Ui::SettingsGUISpinBoxScreen *ui;
};

#endif // SETTINGSGUISPINBOXSCREEN_H
