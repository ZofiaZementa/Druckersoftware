#ifndef SETTINGSHEATINGHOTENDSCREEN_H
#define SETTINGSHEATINGHOTENDSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsHeatingHotEndScreen;
}

class SettingsHeatingHotEndScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsHeatingHotEndScreen(QWidget *parent = 0);
    ~SettingsHeatingHotEndScreen();

private:
    Ui::SettingsHeatingHotEndScreen *ui;
};

#endif // SETTINGSHEATINGHOTENDSCREEN_H
