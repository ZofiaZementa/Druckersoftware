#include "infoioscreen.h"
#include "ui_infoioscreen.h"

InfoIOScreen::InfoIOScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOScreen)
{
    ui->setupUi(this);

    m_infoIOCoreScreen = new InfoIOCoreScreen(this);
    m_infoIODigitalScreen =  new InfoIODigitalScreen(this);
    m_infoIOAnalogOutScreen = new InfoIOAnalogOutScreen(this);
    m_infoIOAnalogInScreen = new InfoIOAnalogInScreen(this);
    m_infoIORTDScreen = new InfoIORTDScreen(this);

    uiSetup();

    QObject::connect(ui->coreButton, SIGNAL(clicked()), this, SLOT(coreButtonCLicked()));
    QObject::connect(ui->digitalButton, SIGNAL(clicked()), this, SLOT(digitalButtonClicked()));
    QObject::connect(ui->analogOutButton, SIGNAL(clicked()), this, SLOT(analogOutButtonClicked()));
    QObject::connect(ui->analogInButton, SIGNAL(clicked()), this, SLOT(analogInButtonClicked()));
    QObject::connect(ui->rtdButton, SIGNAL(clicked()), this, SLOT(rtdButtonClicked()));
}

InfoIOScreen::~InfoIOScreen()
{
    delete ui;
}

void InfoIOScreen::coreButtonCLicked()
{

    m_infoIOCoreScreen->setVisible(true);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogOutScreen->setVisible(false);
    m_infoIOAnalogInScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

    ui->coreButton->setChecked(true);
    ui->digitalButton->setChecked(false);
    ui->analogOutButton->setChecked(false);
    ui->analogInButton->setChecked(false);
    ui->rtdButton->setChecked(false);
}

void InfoIOScreen::digitalButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(true);
    m_infoIOAnalogOutScreen->setVisible(false);
    m_infoIOAnalogInScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

    ui->coreButton->setChecked(false);
    ui->digitalButton->setChecked(true);
    ui->analogOutButton->setChecked(false);
    ui->analogInButton->setChecked(false);
    ui->rtdButton->setChecked(false);
}

void InfoIOScreen::analogOutButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogOutScreen->setVisible(true);
    m_infoIOAnalogInScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

    ui->coreButton->setChecked(false);
    ui->digitalButton->setChecked(false);
    ui->analogOutButton->setChecked(true);
    ui->analogInButton->setChecked(false);
    ui->rtdButton->setChecked(false);
}

void InfoIOScreen::analogInButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogOutScreen->setVisible(false);
    m_infoIOAnalogInScreen->setVisible(true);
    m_infoIORTDScreen->setVisible(false);

    ui->coreButton->setChecked(false);
    ui->digitalButton->setChecked(false);
    ui->analogOutButton->setChecked(false);
    ui->analogInButton->setChecked(true);
    ui->rtdButton->setChecked(false);
}

void InfoIOScreen::rtdButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogOutScreen->setVisible(false);
    m_infoIOAnalogInScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(true);

    ui->coreButton->setChecked(false);
    ui->digitalButton->setChecked(false);
    ui->analogOutButton->setChecked(false);
    ui->analogInButton->setChecked(false);
    ui->rtdButton->setChecked(true);
}

void InfoIOScreen::uiSetup()
{

    m_infoIOCoreScreen->move(0, 41);
    m_infoIODigitalScreen->move(0, 41);
    m_infoIOAnalogOutScreen->move(0, 41);
    m_infoIOAnalogInScreen->move(0, 41);
    m_infoIORTDScreen->move(0, 41);

    m_infoIOCoreScreen->setVisible(true);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogOutScreen->setVisible(false);
    m_infoIOAnalogInScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

    ui->coreButton->setCheckable(true);
    ui->digitalButton->setCheckable(true);
    ui->analogOutButton->setCheckable(true);
    ui->analogInButton->setCheckable(true);
    ui->rtdButton->setCheckable(true);

    ui->coreButton->setChecked(true);
}
