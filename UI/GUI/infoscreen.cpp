#include "infoscreen.h"
#include "ui_infoscreen.h"

InfoScreen::InfoScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoScreen)
{
    ui->setupUi(this);

    m_infoGeneralScreen = new InfoGeneralScreen(this);
    m_infoMotorScreen = new InfoMotorScreen(this);
    m_infoHeatingScreen = new InfoHeatingScreen(this);
    m_infoIOScreen = new InfoIOScreen(this);
    m_infoSerialScreen = new InfoSerialScreen(this);
    m_infoMiscScreen = new InfoMiscScreen(this);

    m_infoGeneralScreen->move(0, 41);
    m_infoMotorScreen->move(0, 41);
    m_infoHeatingScreen->move(0, 41);
    m_infoIOScreen->move(0, 41);
    m_infoSerialScreen->move(0, 41);
    m_infoMiscScreen->move(0, 41);

    m_infoGeneralScreen->setVisible(true);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(false);

    QObject::connect(ui->generalButton, SIGNAL(clicked()), this, SLOT(generalButtonClicked()));
    QObject::connect(ui->motorButton, SIGNAL(clicked()), this, SLOT(motorButtonClicked()));
    QObject::connect(ui->heatingButton, SIGNAL(clicked()), this, SLOT(heatingButtonClicked()));
    QObject::connect(ui->ioButton, SIGNAL(clicked()), this, SLOT(ioButtonClicked()));
    QObject::connect(ui->serialButton, SIGNAL(clicked()), this, SLOT(serialButtonClicked()));
    QObject::connect(ui->miscButton, SIGNAL(clicked()), this, SLOT(miscButtonClicked()));
}

InfoScreen::~InfoScreen()
{
    delete ui;
}

void InfoScreen::generalButtonClicked()
{

    m_infoGeneralScreen->setVisible(true);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(false);
}

void InfoScreen::motorButtonClicked()
{

    m_infoGeneralScreen->setVisible(false);
    m_infoMotorScreen->setVisible(true);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(false);
}

void InfoScreen::heatingButtonClicked()
{

    m_infoGeneralScreen->setVisible(false);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(true);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(false);
}

void InfoScreen::ioButtonClicked()
{

    m_infoGeneralScreen->setVisible(false);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(true);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(false);
}

void InfoScreen::serialButtonClicked()
{

    m_infoGeneralScreen->setVisible(false);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(true);
    m_infoMiscScreen->setVisible(false);
}

void InfoScreen::miscButtonClicked()
{

    m_infoGeneralScreen->setVisible(false);
    m_infoMotorScreen->setVisible(false);
    m_infoHeatingScreen->setVisible(false);
    m_infoIOScreen->setVisible(false);
    m_infoSerialScreen->setVisible(false);
    m_infoMiscScreen->setVisible(true);
}
