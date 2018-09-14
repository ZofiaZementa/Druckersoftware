#include "settingsmotorextruderscreen.h"
#include "ui_settingsmotorextruderscreen.h"

SettingsMotorExtruderScreen::SettingsMotorExtruderScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorExtruderScreen)
{
    ui->setupUi(this);

    m_multiplierSpinBox = new SpinBox(this);
    m_motoradressSpinBox = new SpinBox(this);
    m_maxFeedrateSpinBox = new SpinBox(this);
    m_minStepfrequenzySpinBox = new SpinBox(this);
    m_phasecurrentSpinBox = new SpinBox(this);
    m_haltPhasecurrentSpinBox = new SpinBox(this);
    m_stopDeccelerationSpinBox = new SpinBox(this);
    m_backlashSpinBox = new SpinBox(this);
    m_maxAccelerationSpinBox = new SpinBox(this);
    m_maxDeccelerationSpinBox = new SpinBox(this);
    m_maxAccelerationChangeSpinBox = new SpinBox(this);
    m_maxDeccelerationChangeSpinBox = new SpinBox(this);
    m_settings = new QSettings(this);

    uiSetup();
    uiUpdateSettings();
    uiUpdateValues();
}

SettingsMotorExtruderScreen::~SettingsMotorExtruderScreen()
{
    delete ui;
}

void SettingsMotorExtruderScreen::uiSetup()
{

    m_multiplierSpinBox->resize(193, 40);
    m_motoradressSpinBox->resize(193, 40);
    m_maxFeedrateSpinBox->resize(193, 40);
    m_minStepfrequenzySpinBox->resize(193, 40);
    m_phasecurrentSpinBox->resize(193, 40);
    m_haltPhasecurrentSpinBox->resize(193, 40);
    m_stopDeccelerationSpinBox->resize(193, 40);
    m_backlashSpinBox->resize(193, 40);
    m_maxAccelerationSpinBox->resize(193, 40);
    m_maxDeccelerationSpinBox->resize(193, 40);
    m_maxAccelerationChangeSpinBox->resize(193, 40);
    m_maxDeccelerationChangeSpinBox->resize(193, 40);

    m_multiplierSpinBox->move(40, 57);
    m_motoradressSpinBox->move(40, 154);
    m_maxFeedrateSpinBox->move(40, 251);
    m_minStepfrequenzySpinBox->move(40, 348);
    m_phasecurrentSpinBox->move(273, 154);
    m_haltPhasecurrentSpinBox->move(273, 251);
    m_stopDeccelerationSpinBox->move(273, 348);
    m_backlashSpinBox->move(273, 445);
    m_maxAccelerationSpinBox->move(506, 57);
    m_maxDeccelerationSpinBox->move(506, 154);
    m_maxAccelerationChangeSpinBox->move(506, 251);
    m_maxDeccelerationChangeSpinBox->move(506, 348);

    m_motoradressSpinBox->setDecimals(0);
    m_minStepfrequenzySpinBox->setDecimals(0);
    m_phasecurrentSpinBox->setDecimals(0);
    m_haltPhasecurrentSpinBox->setDecimals(0);
    m_stopDeccelerationSpinBox->setDecimals(0);
}

void SettingsMotorExtruderScreen::uiUpdateSettings()
{

    m_multiplierSpinBox->setMinimum(0.0);
    m_motoradressSpinBox->setMinimum(0.0);
    m_maxFeedrateSpinBox->setMinimum(0.0);
    m_minStepfrequenzySpinBox->setMinimum(0.0);
    m_phasecurrentSpinBox->setMinimum(0.0);
    m_haltPhasecurrentSpinBox->setMinimum(0.0);
    m_stopDeccelerationSpinBox->setMinimum(0.0);
    m_backlashSpinBox->setMinimum(0.0);
    m_maxAccelerationSpinBox->setMinimum(0.0);
    m_maxDeccelerationSpinBox->setMinimum(0.0);
    m_maxAccelerationChangeSpinBox->setMinimum(0.0);
    m_maxDeccelerationChangeSpinBox->setMinimum(0.0);

    m_multiplierSpinBox->setMaximumOn(false);
    m_maxFeedrateSpinBox->setMaximumOn(false);
    m_maxAccelerationSpinBox->setMaximum(false);
    m_maxDeccelerationSpinBox->setMaximum(false);
    m_maxAccelerationChangeSpinBox->setMaximum(false);
    m_maxDeccelerationChangeSpinBox->setMaximum(false);

    m_motoradressSpinBox->setMaximum(254.0);
    m_minStepfrequenzySpinBox->setMaximum(160000.0);
    m_phasecurrentSpinBox->setMaximum(100.0);
    m_haltPhasecurrentSpinBox->setMaximum(100.0);
    m_stopDeccelerationSpinBox->setMaximum(8000.0);
    m_backlashSpinBox->setMaximum(9999.0);

    m_multiplierSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_motoradressSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxFeedrateSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_minStepfrequenzySpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_phasecurrentSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_haltPhasecurrentSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_stopDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_backlashSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxAccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxAccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxDeccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());

    m_multiplierSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_motoradressSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxFeedrateSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_minStepfrequenzySpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_phasecurrentSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_haltPhasecurrentSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_stopDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_backlashSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxAccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxAccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxDeccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());

    m_multiplierSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_motoradressSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxFeedrateSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_minStepfrequenzySpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_phasecurrentSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_haltPhasecurrentSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_stopDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_backlashSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxAccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxAccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxDeccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());

    ui->negativeTurningDirectionComboBox->addItem(QString("0"), 0);
    ui->negativeTurningDirectionComboBox->addItem(QString("1"), 1);

    ui->positiveTurningDirectionComboBox->addItem(QString("0"), 0);
    ui->positiveTurningDirectionComboBox->addItem(QString("1"), 1);
}

void SettingsMotorExtruderScreen::uiUpdateValues()
{

    m_multiplierSpinBox->setValue(m_settings->value("motorsettings/extruder/multiplier", 100.0).toReal());
    m_motoradressSpinBox->setValue(m_settings->value("motorsettings/extruder/maximum_feedrate", 100.0).toReal());
    m_maxFeedrateSpinBox->setValue(m_settings->value("motorsettings/extruder/motoradress", 1.0).toReal());
    m_minStepfrequenzySpinBox->setValue(m_settings->value("motorsettings/extruder/min_stepfrequency", 0.0).toReal());
    m_phasecurrentSpinBox->setValue(m_settings->value("motorsettings/extruder/phasecurrent", 100.0).toReal());
    m_haltPhasecurrentSpinBox->setValue(m_settings->value("motorsettings/extruder/haltphasecurrent", 25.0).toReal());
    m_stopDeccelerationSpinBox->setValue(m_settings->value("motorsettings/extruder/stop_decceleration", 8000.0).toReal());
    m_backlashSpinBox->setValue(m_settings->value("motorsettings/extruder/backlash", 0.0).toReal());
    m_maxAccelerationSpinBox->setValue(m_settings->value("motorsettings/extruder/maximum_acceleration", 500.0).toReal());
    m_maxDeccelerationSpinBox->setValue(m_settings->value("motorsettings/extruder/maximum_decceleration", 500.0).toReal());
    m_maxAccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/extruder/maximum_acceleration_change", 100.0).toReal());
    m_maxDeccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/extruder/maximum_decceleration_change", 100.0).toReal());

    if(m_settings->value("motorsettings/extruder/negative_turningdirection", 0).toInt() == 0){

        ui->negativeTurningDirectionComboBox->setCurrentIndex(0);
    }

    else if(m_settings->value("motorsettings/extruder/negative_turningdirection", 0).toInt() == 1){

        ui->negativeTurningDirectionComboBox->setCurrentIndex(1);
    }

    if(m_settings->value("motorsettings/extruder/positive_turningdirection", 1).toInt() == 0){

        ui->positiveTurningDirectionComboBox->setCurrentIndex(0);
    }
    else if(m_settings->value("motorsettings/extruder/positive_turningdirection", 1).toInt() == 1){

        ui->positiveTurningDirectionComboBox->setCurrentIndex(1);
    }
}

