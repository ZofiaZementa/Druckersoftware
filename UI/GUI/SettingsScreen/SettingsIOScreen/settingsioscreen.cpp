#include "settingsioscreen.h"
#include "ui_settingsioscreen.h"

SettingsIOScreen::SettingsIOScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsIOScreen)
{
    ui->setupUi(this);

    m_settingsIOSensorScreen = new SettingsIOSensorScreen(this);
    m_settingsIOHeatingScreen = new SettingsIOHeatingScreen(this);
    m_settingsIOLightingScreen = new SettingsIOLightingScreen(this);
    m_settingsIOMiscScreen = new SettingsIOMiscScreen(this);

    m_settingsIOSensorScreen->move(0, 41);
    m_settingsIOHeatingScreen->move(0, 41);
    m_settingsIOLightingScreen->move(0, 41);
    m_settingsIOMiscScreen->move(0, 41);

    m_settingsIOHeatingScreen->setVisible(false);
    m_settingsIOLightingScreen->setVisible(false);
    m_settingsIOMiscScreen->setVisible(false);

    ui->sensorButton->setChecked(true);

    QObject::connect(ui->sensorButton, SIGNAL(clicked()), this, SLOT(sensorButtonClicked()));
    QObject::connect(ui->heatingButton, SIGNAL(clicked()), this, SLOT(heatingButtonClicked()));
    QObject::connect(ui->lightingButton, SIGNAL(clicked()), this, SLOT(lightingButtonClicked()));
    QObject::connect(ui->miscButton, SIGNAL(clicked()), this, SLOT(miscButtonClicked()));
}

SettingsIOScreen::~SettingsIOScreen()
{
    delete ui;
}

void SettingsIOScreen::sensorButtonClicked()
{

    m_settingsIOSensorScreen->setVisible(true);
    m_settingsIOHeatingScreen->setVisible(false);
    m_settingsIOLightingScreen->setVisible(false);
    m_settingsIOMiscScreen->setVisible(false);

    ui->sensorButton->setChecked(true);
    ui->heatingButton->setChecked(false);
    ui->lightingButton->setChecked(false);
    ui->miscButton->setChecked(false);
}

void SettingsIOScreen::heatingButtonClicked()
{

    m_settingsIOSensorScreen->setVisible(false);
    m_settingsIOHeatingScreen->setVisible(true);
    m_settingsIOLightingScreen->setVisible(false);
    m_settingsIOMiscScreen->setVisible(false);

    ui->sensorButton->setChecked(false);
    ui->heatingButton->setChecked(true);
    ui->lightingButton->setChecked(false);
    ui->miscButton->setChecked(false);
}

void SettingsIOScreen::lightingButtonClicked()
{

    m_settingsIOSensorScreen->setVisible(false);
    m_settingsIOHeatingScreen->setVisible(false);
    m_settingsIOLightingScreen->setVisible(true);
    m_settingsIOMiscScreen->setVisible(false);

    ui->sensorButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->lightingButton->setChecked(true);
    ui->miscButton->setChecked(false);
}

void SettingsIOScreen::miscButtonClicked()
{

    m_settingsIOSensorScreen->setVisible(false);
    m_settingsIOHeatingScreen->setVisible(false);
    m_settingsIOLightingScreen->setVisible(false);
    m_settingsIOMiscScreen->setVisible(true);

    ui->sensorButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->lightingButton->setChecked(false);
    ui->miscButton->setChecked(true);
}
