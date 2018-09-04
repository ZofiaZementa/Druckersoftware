#ifndef SETTINGSMOTORSCREEN_H
#define SETTINGSMOTORSCREEN_H

#include <QWidget>
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorgeneralscreen.h"
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorxaxisscreen.h"
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotoryaxisscreen.h"
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorzaxisscreen.h"
#include "UI/GUI/SettingsScreen/SettingsMotorScreen/settingsmotorextruderscreen.h"

namespace Ui {
class SettingsMotorScreen;
}

class SettingsMotorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorScreen(QWidget *parent = 0);
    ~SettingsMotorScreen();

private slots:

    void generalButtonClicked();
    void xAxisButtonClicked();
    void yAxisButtonClicked();
    void zAxisButtonClicked();
    void extruderButtonClicked();

private:

    Ui::SettingsMotorScreen *ui;
    SettingsMotorGeneralScreen *m_settingsMotorGeneralScreen;
    SettingsMotorXAxisScreen *m_settngsMotorXAxisScreen;
    SettingsMotorYAxisScreen *m_settngsMotorYAxisScreen;
    SettingsMotorZAxisScreen *m_settngsMotorZAxisScreen;
    SettingsMotorExtruderScreen *m_settngsMotorExtruderScreen;
};

#endif // SETTINGSMOTORSCREEN_H
