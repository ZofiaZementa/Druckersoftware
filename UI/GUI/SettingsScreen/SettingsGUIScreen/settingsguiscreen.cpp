#include "settingsguiscreen.h"
#include "ui_settingsguiscreen.h"

SettingsGUIScreen::SettingsGUIScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsGUIScreen)
{
    ui->setupUi(this);

    m_settingsGUIManualScreen = new SettingsGUIManualScreen(this);
    m_settingsGUISpinBoxScreen = new SettingsGUISpinBoxScreen(this);

    m_settingsGUIManualScreen->move(0, 41);
    m_settingsGUISpinBoxScreen->move(0, 41);

    m_settingsGUISpinBoxScreen->setVisible(false);

    ui->manualScreenButton->setChecked(true);

    QObject::connect(ui->manualScreenButton, SIGNAL(clicked()), this, SLOT(manualScreenButtonClicked()));
    QObject::connect(ui->spinBoxButton, SIGNAL(clicked()), this, SLOT(spinBoxButtonClicked()));
}

SettingsGUIScreen::~SettingsGUIScreen()
{
    delete ui;
}

void SettingsGUIScreen::manualScreenButtonClicked()
{

    m_settingsGUIManualScreen->setVisible(true);
    m_settingsGUISpinBoxScreen->setVisible(false);

    ui->manualScreenButton->setChecked(true);
    ui->spinBoxButton->setChecked(false);
}

void SettingsGUIScreen::spinBoxButtonClicked()
{

    m_settingsGUIManualScreen->setVisible(false);
    m_settingsGUISpinBoxScreen->setVisible(true);

    ui->manualScreenButton->setChecked(false);
    ui->spinBoxButton->setChecked(true);
}
