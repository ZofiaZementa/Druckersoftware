#ifndef SETTINGSGUIMANUALSCREEN_H
#define SETTINGSGUIMANUALSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsGUIManualScreen;
}

class SettingsGUIManualScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsGUIManualScreen(QWidget *parent = 0);
    ~SettingsGUIManualScreen();

private:
    Ui::SettingsGUIManualScreen *ui;
};

#endif // SETTINGSGUIMANUALSCREEN_H
