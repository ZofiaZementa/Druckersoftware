#include "settingsmotorscreen.h"
#include "ui_settingsmotorscreen.h"

SettingsMotorScreen::SettingsMotorScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMotorScreen)
{
    ui->setupUi(this);

    m_settingsMotorGeneralScreen = new SettingsMotorGeneralScreen(this);
    m_settngsMotorXAxisScreen = new SettingsMotorXAxisScreen(this);
    m_settngsMotorYAxisScreen = new SettingsMotorYAxisScreen(this);
    m_settngsMotorZAxisScreen = new SettingsMotorZAxisScreen(this);
    m_settngsMotorExtruderScreen = new SettingsMotorExtruderScreen(this);

    m_settingsMotorGeneralScreen->move(0, 41);
    m_settngsMotorXAxisScreen->move(0, 41);
    m_settngsMotorYAxisScreen->move(0, 41);
    m_settngsMotorZAxisScreen->move(0, 41);
    m_settngsMotorExtruderScreen->move(0, 41);

    m_settngsMotorXAxisScreen->setVisible(false);
    m_settngsMotorYAxisScreen->setVisible(false);
    m_settngsMotorZAxisScreen->setVisible(false);
    m_settngsMotorExtruderScreen->setVisible(false);

    ui->generalButton->setChecked(true);

    QObject::connect(ui->generalButton, SIGNAL(clicked()), this, SLOT(generalButtonClicked()));
    QObject::connect(ui->xAxisButton, SIGNAL(clicked()), this, SLOT(xAxisButtonClicked()));
    QObject::connect(ui->yAxiButton, SIGNAL(clicked()), this, SLOT(yAxisButtonClicked()));
    QObject::connect(ui->zAxisButton, SIGNAL(clicked()), this, SLOT(zAxisButtonClicked()));
    QObject::connect(ui->extruderButton, SIGNAL(clicked()), this, SLOT(extruderButtonClicked()));
}

SettingsMotorScreen::~SettingsMotorScreen()
{
    delete ui;
}

void SettingsMotorScreen::generalButtonClicked()
{

    m_settingsMotorGeneralScreen->setVisible(true);
    m_settngsMotorXAxisScreen->setVisible(false);
    m_settngsMotorYAxisScreen->setVisible(false);
    m_settngsMotorZAxisScreen->setVisible(false);
    m_settngsMotorExtruderScreen->setVisible(false);

    ui->generalButton->setChecked(true);
    ui->xAxisButton->setChecked(false);
    ui->yAxiButton->setChecked(false);
    ui->zAxisButton->setChecked(false);
    ui->extruderButton->setChecked(false);
}

void SettingsMotorScreen::xAxisButtonClicked()
{

    m_settingsMotorGeneralScreen->setVisible(false);
    m_settngsMotorXAxisScreen->setVisible(true);
    m_settngsMotorYAxisScreen->setVisible(false);
    m_settngsMotorZAxisScreen->setVisible(false);
    m_settngsMotorExtruderScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->xAxisButton->setChecked(true);
    ui->yAxiButton->setChecked(false);
    ui->zAxisButton->setChecked(false);
    ui->extruderButton->setChecked(false);
}

void SettingsMotorScreen::yAxisButtonClicked()
{

    m_settingsMotorGeneralScreen->setVisible(false);
    m_settngsMotorXAxisScreen->setVisible(false);
    m_settngsMotorYAxisScreen->setVisible(true);
    m_settngsMotorZAxisScreen->setVisible(false);
    m_settngsMotorExtruderScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->xAxisButton->setChecked(false);
    ui->yAxiButton->setChecked(true);
    ui->zAxisButton->setChecked(false);
    ui->extruderButton->setChecked(false);
}

void SettingsMotorScreen::zAxisButtonClicked()
{

    m_settingsMotorGeneralScreen->setVisible(false);
    m_settngsMotorXAxisScreen->setVisible(false);
    m_settngsMotorYAxisScreen->setVisible(false);
    m_settngsMotorZAxisScreen->setVisible(true);
    m_settngsMotorExtruderScreen->setVisible(false);

    ui->generalButton->setChecked(false);
    ui->xAxisButton->setChecked(false);
    ui->yAxiButton->setChecked(false);
    ui->zAxisButton->setChecked(true);
    ui->extruderButton->setChecked(false);
}

void SettingsMotorScreen::extruderButtonClicked()
{

    m_settingsMotorGeneralScreen->setVisible(false);
    m_settngsMotorXAxisScreen->setVisible(false);
    m_settngsMotorYAxisScreen->setVisible(false);
    m_settngsMotorZAxisScreen->setVisible(false);
    m_settngsMotorExtruderScreen->setVisible(true);

    ui->generalButton->setChecked(false);
    ui->xAxisButton->setChecked(false);
    ui->yAxiButton->setChecked(false);
    ui->zAxisButton->setChecked(false);
    ui->extruderButton->setChecked(true);
}
