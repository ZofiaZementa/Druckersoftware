#include "settingsscreen.h"
#include "ui_settingsscreen.h"

SettingsScreen::SettingsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen)
{
    ui->setupUi(this);

    m_settingsGeneralScreen = new SettingsGeneralScreen(this);
    m_settingsMotorScreen = new SettingsMotorScreen(this);
    m_settingsGUIScreen = new SettingsGUIScreen(this);
    m_settingsHeatingScreen = new SettingsHeatingScreen(this);
    m_settingsIOScreen = new SettingsIOScreen(this);
    m_settingsLoggingScreen = new SettingsLoggingScreen(this);
    m_settingsSerialScreen = new SettingsSerialScreen(this);

    m_settingsGeneralScreen->move(0, 41);
    m_settingsMotorScreen->move(0, 41);
    m_settingsGUIScreen->move(0, 41);
    m_settingsHeatingScreen->move(0, 41);
    m_settingsIOScreen->move(0, 41);
    m_settingsLoggingScreen->move(0, 41);
    m_settingsSerialScreen->move(0, 41);

    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(true);

    QObject::connect(ui->generalButton, SIGNAL(clicked()), this, SLOT(generalButtonClicked()));
    QObject::connect(ui->motorsButton, SIGNAL(clicked()), this, SLOT(motorButtonClicked()));
    QObject::connect(ui->guiButton, SIGNAL(clicked()), this, SLOT(guiButtonClicked()));
    QObject::connect(ui->heatingButton, SIGNAL(clicked()), this, SLOT(heatingButtonClicked()));
    QObject::connect(ui->ioButton, SIGNAL(clicked()), this, SLOT(ioButonClicked()));
    QObject::connect(ui->loggingButton, SIGNAL(clicked()), this, SLOT(loggingButtonClicked()));
    QObject::connect(ui->serialButton, SIGNAL(clicked()), this, SLOT(serialButtonClicked()));
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::generalButtonClicked()
{

    m_settingsGeneralScreen->setVisible(true);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(true);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::motorButtonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(true);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(true);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::guiButtonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(true);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(true);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::heatingButtonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(true);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(true);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::ioButonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(true);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(true);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::loggingButtonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(true);
    m_settingsSerialScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(true);
    ui->serialButton->setChecked(false);
}

void SettingsScreen::serialButtonClicked()
{

    m_settingsGeneralScreen->setVisible(false);
    m_settingsMotorScreen->setVisible(false);
    m_settingsGUIScreen->setVisible(false);
    m_settingsHeatingScreen->setVisible(false);
    m_settingsIOScreen->setVisible(false);
    m_settingsLoggingScreen->setVisible(false);
    m_settingsSerialScreen->setVisible(true);

    ui->generalButton->setChecked(false);
    ui->motorsButton->setChecked(false);
    ui->guiButton->setChecked(false);
    ui->heatingButton->setChecked(false);
    ui->ioButton->setChecked(false);
    ui->loggingButton->setChecked(false);
    ui->serialButton->setChecked(true);
}
