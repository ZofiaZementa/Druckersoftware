#include "settingsmotorgeneralscreen.h"
#include "ui_settingsmotorgeneralscreen.h"

SettingsMotorGeneralScreen::SettingsMotorGeneralScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorGeneralScreen)
{
    ui->setupUi(this);

    m_maxTravelAccelerationSpinBox = new SpinBox(this);
    m_maxPrintAccelerationSpinBox = new SpinBox(this);
    m_defaultTravelAccelerationSpinBox = new SpinBox(this);
    m_defaultPrintAccelerationSpinBox = new SpinBox(this);
    m_maxTravelDeccelerationSpinBox = new SpinBox(this);
    m_maxPrintDeccelerationSpinBox = new SpinBox(this);
    m_defaultTravelDeccelerationSpinBox = new SpinBox(this);
    m_defaultPrintDeccelerationSpinBox = new SpinBox(this);
    m_maxAccelerationChangeSpinBox = new SpinBox(this);
    m_defaultAccelerationChangeSpinBox = new SpinBox(this);
    m_maxDeccelerationChangeSpinBox = new SpinBox(this);
    m_defaultDeccelerationChangeSpinBox = new SpinBox(this);
    m_tempCheckIntervalSpinBox = new SpinBox(this);
    m_maxTravelFeedrateSpinBox = new SpinBox(this);
    m_maxPrintFeedrateSpinBox = new SpinBox(this);
    m_defaultTravelFeedrateSpinBox = new SpinBox(this);
    m_defaultPrintFeedrateSpinBox = new SpinBox(this);
    m_settings = new QSettings(QString("./settings.ini"), QSettings::IniFormat, this);

    uiSetup();
    uiUpdateSettings();
    uiUpdateValues();
}

SettingsMotorGeneralScreen::~SettingsMotorGeneralScreen()
{
    delete ui;
}

void SettingsMotorGeneralScreen::uiSetup()
{

    m_maxTravelAccelerationSpinBox->resize(193, 40);
    m_maxPrintAccelerationSpinBox->resize(193, 40);
    m_defaultTravelAccelerationSpinBox->resize(193, 40);
    m_defaultPrintAccelerationSpinBox->resize(193, 40);
    m_maxTravelDeccelerationSpinBox->resize(193, 40);
    m_maxPrintDeccelerationSpinBox->resize(193, 40);
    m_defaultTravelDeccelerationSpinBox->resize(193, 40);
    m_defaultPrintDeccelerationSpinBox->resize(193, 40);
    m_maxAccelerationChangeSpinBox->resize(193, 40);
    m_defaultAccelerationChangeSpinBox->resize(193, 40);
    m_maxDeccelerationChangeSpinBox->resize(193, 40);
    m_defaultDeccelerationChangeSpinBox->resize(193, 40);
    m_tempCheckIntervalSpinBox->resize(193, 40);
    m_maxTravelFeedrateSpinBox->resize(193, 40);
    m_maxPrintFeedrateSpinBox->resize(193, 40);
    m_defaultTravelFeedrateSpinBox->resize(193, 40);
    m_defaultPrintFeedrateSpinBox->resize(193, 40);

    m_maxTravelAccelerationSpinBox->move(40, 43);
    m_maxPrintAccelerationSpinBox->move(40, 126);
    m_defaultTravelAccelerationSpinBox->move(40, 209);
    m_defaultPrintAccelerationSpinBox->move(40, 292);
    m_maxTravelDeccelerationSpinBox->move(40, 375);
    m_maxPrintDeccelerationSpinBox->move(40, 458);
    m_defaultTravelDeccelerationSpinBox->move(273, 43);
    m_defaultPrintDeccelerationSpinBox->move(273, 126);
    m_maxAccelerationChangeSpinBox->move(273, 209);
    m_defaultAccelerationChangeSpinBox->move(273, 292);
    m_maxDeccelerationChangeSpinBox->move(273, 375);
    m_defaultDeccelerationChangeSpinBox->move(273, 458);
    m_tempCheckIntervalSpinBox->move(506, 126);
    m_maxTravelFeedrateSpinBox->move(506, 209);
    m_maxPrintFeedrateSpinBox->move(506, 292);
    m_defaultTravelFeedrateSpinBox->move(506, 375);
    m_defaultPrintFeedrateSpinBox->move(506, 458);

    m_tempCheckIntervalSpinBox->setDecimals(0);
}

void SettingsMotorGeneralScreen::uiUpdateSettings()
{

    m_maxTravelAccelerationSpinBox->setMinimum(0.0);
    m_maxPrintAccelerationSpinBox->setMinimum(0.0);
    m_defaultTravelAccelerationSpinBox->setMinimum(0.0);
    m_defaultPrintAccelerationSpinBox->setMinimum(0.0);
    m_maxTravelDeccelerationSpinBox->setMinimum(0.0);
    m_maxPrintDeccelerationSpinBox->setMinimum(0.0);
    m_defaultTravelDeccelerationSpinBox->setMinimum(0.0);
    m_defaultPrintDeccelerationSpinBox->setMinimum(0.0);
    m_maxAccelerationChangeSpinBox->setMinimum(0.0);
    m_defaultAccelerationChangeSpinBox->setMinimum(0.0);
    m_maxDeccelerationChangeSpinBox->setMinimum(0.0);
    m_defaultDeccelerationChangeSpinBox->setMinimum(0.0);
    m_tempCheckIntervalSpinBox->setMinimum(0.0);
    m_defaultTravelFeedrateSpinBox->setMinimum(0.0);
    m_defaultPrintFeedrateSpinBox->setMinimum(0.0);

    m_maxTravelAccelerationSpinBox->setMaximumOn(false);
    m_maxPrintAccelerationSpinBox->setMaximumOn(false);
    m_defaultTravelAccelerationSpinBox->setMaximumOn(false);
    m_defaultPrintAccelerationSpinBox->setMaximumOn(false);
    m_maxTravelDeccelerationSpinBox->setMaximumOn(false);
    m_maxPrintDeccelerationSpinBox->setMaximumOn(false);
    m_defaultTravelDeccelerationSpinBox->setMaximumOn(false);
    m_defaultPrintDeccelerationSpinBox->setMaximumOn(false);
    m_maxAccelerationChangeSpinBox->setMaximumOn(false);
    m_defaultAccelerationChangeSpinBox->setMaximumOn(false);
    m_maxDeccelerationChangeSpinBox->setMaximumOn(false);
    m_defaultDeccelerationChangeSpinBox->setMaximumOn(false);
    m_maxTravelFeedrateSpinBox->setMaximumOn(false);
    m_maxPrintFeedrateSpinBox->setMaximumOn(false);
    m_defaultTravelFeedrateSpinBox->setMaximumOn(false);
    m_defaultPrintFeedrateSpinBox->setMaximumOn(false);

    m_tempCheckIntervalSpinBox->setMaximum(10000.0);

    m_maxTravelAccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxPrintAccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultTravelAccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultPrintAccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxTravelDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxPrintDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultTravelDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultPrintDeccelerationSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxAccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultAccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxDeccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultDeccelerationChangeSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_tempCheckIntervalSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxTravelFeedrateSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_maxPrintFeedrateSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultTravelFeedrateSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    m_defaultPrintFeedrateSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());

    m_maxTravelAccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxPrintAccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultTravelAccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultPrintAccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxTravelDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxPrintDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultTravelDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultPrintDeccelerationSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxAccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultAccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxDeccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultDeccelerationChangeSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_tempCheckIntervalSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxTravelFeedrateSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_maxPrintFeedrateSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultTravelFeedrateSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    m_defaultPrintFeedrateSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());

    m_maxTravelAccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxPrintAccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultTravelAccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultPrintAccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxTravelDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxPrintDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultTravelDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultPrintDeccelerationSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxAccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultAccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxDeccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultDeccelerationChangeSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_tempCheckIntervalSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxTravelFeedrateSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_maxPrintFeedrateSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultTravelFeedrateSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    m_defaultPrintFeedrateSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());

    ui->stepSizeComboBox->addItem(QString("1"), 1.0);
    ui->stepSizeComboBox->addItem(QString("2"), 2.0);
    ui->stepSizeComboBox->addItem(QString("4"), 4.0);
    ui->stepSizeComboBox->addItem(QString("8"), 8.0);
    ui->stepSizeComboBox->addItem(QString("16"), 16.0);
    ui->stepSizeComboBox->addItem(QString("32"), 32.0);
    ui->stepSizeComboBox->addItem(QString("64"), 64.0);
}

void SettingsMotorGeneralScreen::uiUpdateValues()
{

    m_maxTravelAccelerationSpinBox->setValue(m_settings->value("motorsettings/maximum_travel_acceleration", 100.0).toReal());
    m_maxPrintAccelerationSpinBox->setValue(m_settings->value("motorsettings/maximum_printing_acceleration", 500.0).toReal());
    m_defaultTravelAccelerationSpinBox->setValue(m_settings->value("motorsettings/default_travel_acceleration", 100.0).toReal());
    m_defaultPrintAccelerationSpinBox->setValue(m_settings->value("motorsettings/default_printing_acceleration", 500.0).toReal());
    m_maxTravelDeccelerationSpinBox->setValue(m_settings->value("motorsettings/maximum_travel_decceleration", 100.0).toReal());
    m_maxPrintDeccelerationSpinBox->setValue(m_settings->value("motorsettings/maximum_printing_decceleration", 500.0).toReal());
    m_defaultTravelDeccelerationSpinBox->setValue(m_settings->value("motorsettings/default_travel_decceleration", 100.0).toReal());
    m_defaultPrintDeccelerationSpinBox->setValue(m_settings->value("motorsettings/default_printing_decceleration", 500.0).toReal());
    m_maxAccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/maximum_acceleration_change", 100.0).toReal());
    m_defaultAccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/default_acceleration_change", 100.0).toReal());
    m_maxDeccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/maximum_decceleration_change", 100.0).toReal());
    m_defaultDeccelerationChangeSpinBox->setValue(m_settings->value("motorsettings/default_decceleration_change", 100.0).toReal());
    m_tempCheckIntervalSpinBox->setValue(m_settings->value("motorsettings/tempcheckinterval", 1000.0).toReal());
    m_maxTravelFeedrateSpinBox->setValue(m_settings->value("motorsettings/maximum_travel_feedrate", 100.0).toReal());
    m_maxPrintFeedrateSpinBox->setValue(m_settings->value("motorsettings/maximum_printing_feedrate", 100.0).toReal());
    m_defaultTravelFeedrateSpinBox->setValue(m_settings->value("motorsettings/default_travel_feedrate", 100.0).toReal());
    m_defaultPrintFeedrateSpinBox->setValue(m_settings->value("motorsettings/default_printing_feedrate", 100.0).toReal());
    m_settings->sync();

    if(m_settings->value("motorsettings/stepsize", 64).toReal() == 1.0){

        ui->stepSizeComboBox->setCurrentIndex(0);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 2.0){

        ui->stepSizeComboBox->setCurrentIndex(1);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 4.0){

        ui->stepSizeComboBox->setCurrentIndex(2);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 8.0){

        ui->stepSizeComboBox->setCurrentIndex(3);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 16.0){

        ui->stepSizeComboBox->setCurrentIndex(4);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 32.0){

        ui->stepSizeComboBox->setCurrentIndex(5);
    }

    else if(m_settings->value("motorsettings/stepsize", 64).toReal() == 64.0){

        ui->stepSizeComboBox->setCurrentIndex(6);
    }
}
