#ifndef SETTINGSGUISCREEN_H
#define SETTINGSGUISCREEN_H

#include <QWidget>
#include "UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguimanualscreen.h"
#include "UI/GUI/SettingsScreen/SettingsGUIScreen/settingsguispinboxscreen.h"

namespace Ui {
class SettingsGUIScreen;
}

class SettingsGUIScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsGUIScreen(QWidget *parent = 0);
    ~SettingsGUIScreen();

private slots:

    void manualScreenButtonClicked();
    void spinBoxButtonClicked();

private:

    Ui::SettingsGUIScreen *ui;
    SettingsGUIManualScreen *m_settingsGUIManualScreen;
    SettingsGUISpinBoxScreen *m_settingsGUISpinBoxScreen;
};

#endif // SETTINGSGUISCREEN_H
