#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = 0);
    ~SettingsScreen();

private:
    Ui::SettingsScreen *ui;
};

#endif // SETTINGSSCREEN_H
