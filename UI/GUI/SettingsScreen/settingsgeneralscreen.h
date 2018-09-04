#ifndef SETTINGSGENERALSCREEN_H
#define SETTINGSGENERALSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsGeneralScreen;
}

class SettingsGeneralScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsGeneralScreen(QWidget *parent = 0);
    ~SettingsGeneralScreen();

private:
    Ui::SettingsGeneralScreen *ui;
};

#endif // SETTINGSGENERALSCREEN_H
