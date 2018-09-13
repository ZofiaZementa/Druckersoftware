#ifndef SETTINGSMOTORGENERALSCREEN_H
#define SETTINGSMOTORGENERALSCREEN_H

#include <QWidget>
#include <QSettings>
#include "UI/GUI/spinbox.h"

namespace Ui {
class SettingsMotorGeneralScreen;
}

class SettingsMotorGeneralScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMotorGeneralScreen(QWidget *parent = 0);
    ~SettingsMotorGeneralScreen();

private:

    void uiSetup();
    void uiUpdateSettings();
    void uiUpdateValues();

    Ui::SettingsMotorGeneralScreen *ui;
    SpinBox *m_maxTravelAccelerationSpinBox;
    SpinBox *m_maxPrintAccelerationSpinBox;
    SpinBox *m_defaultTravelAccelerationSpinBox;
    SpinBox *m_defaultPrintAccelerationSpinBox;
    SpinBox *m_maxTravelDeccelerationSpinBox;
    SpinBox *m_maxPrintDeccelerationSpinBox;
    SpinBox *m_defaultTravelDeccelerationSpinBox;
    SpinBox *m_defaultPrintDeccelerationSpinBox;
    SpinBox *m_maxAccelerationChangeSpinBox;
    SpinBox *m_defaultAccelerationChangeSpinBox;
    SpinBox *m_maxDeccelerationChangeSpinBox;
    SpinBox *m_defaultDeccelerationChangeSpinBox;
    SpinBox *m_tempCheckIntervalSpinBox;
    SpinBox *m_maxTravelFeedrateSpinBox;
    SpinBox *m_maxPrintFeedrateSpinBox;
    SpinBox *m_defaultTravelFeedrateSpinBox;
    SpinBox *m_defaultPrintFeedrateSpinBox;
    QSettings *m_settings;
};

#endif // SETTINGSMOTORGENERALSCREEN_H
