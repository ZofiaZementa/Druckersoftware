#include "settingsheatingscreen.h"
#include "ui_settingsheatingscreen.h"

SettingsHeatingScreen::SettingsHeatingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsHeatingScreen)
{
    ui->setupUi(this);

    m_settingsHeatingHotEndScreen = new SettingsHeatingHotEndScreen(this);
    m_settingsHeatingBedScreen = new SettingsHeatingBedScreen(this);

    m_settingsHeatingHotEndScreen->move(0, 41);
    m_settingsHeatingBedScreen->move(0, 41);

    m_settingsHeatingBedScreen->setVisible(false);

    ui->hotEndButton->setChecked(true);

    QObject::connect(ui->hotEndButton, SIGNAL(clicked()), this, SLOT(hotEndButtonClicked()));
    QObject::connect(ui->bedButton, SIGNAL(clicked()), this, SLOT(bedButtonClicked()));
}

SettingsHeatingScreen::~SettingsHeatingScreen()
{
    delete ui;
}

void SettingsHeatingScreen::hotEndButtonClicked()
{

    m_settingsHeatingHotEndScreen->setVisible(true);
    m_settingsHeatingBedScreen->setVisible(false);

    ui->hotEndButton->setChecked(true);
    ui->bedButton->setChecked(false);
}

void SettingsHeatingScreen::bedButtonClicked()
{

    m_settingsHeatingHotEndScreen->setVisible(false);
    m_settingsHeatingBedScreen->setVisible(true);

    ui->hotEndButton->setChecked(false);
    ui->bedButton->setChecked(true);
}
