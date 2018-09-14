#ifndef SETTINGSMOTOREXTRUDERSCREEN_H
#define SETTINGSMOTOREXTRUDERSCREEN_H

#include <QWidget>
#include <QSettings>
#include "UI/GUI/spinbox.h"

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

    void uiSetup();
    void uiUpdateSettings();
    void uiUpdateValues();

    Ui::SettingsMotorExtruderScreen *ui;
    SpinBox *m_multiplierSpinBox;
    SpinBox *m_motoradressSpinBox;
    SpinBox *m_maxFeedrateSpinBox;
    SpinBox *m_minStepfrequenzySpinBox;
    SpinBox *m_phasecurrentSpinBox;
    SpinBox *m_haltPhasecurrentSpinBox;
    SpinBox *m_stopDeccelerationSpinBox;
    SpinBox *m_backlashSpinBox;
    SpinBox *m_maxAccelerationSpinBox;
    SpinBox *m_maxDeccelerationSpinBox;
    SpinBox *m_maxAccelerationChangeSpinBox;
    SpinBox *m_maxDeccelerationChangeSpinBox;
    QSettings *m_settings;
};

#endif // SETTINGSMOTOREXTRUDERSCREEN_H
