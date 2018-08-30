#include "infoioscreen.h"
#include "ui_infoioscreen.h"

InfoIOScreen::InfoIOScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOScreen)
{
    ui->setupUi(this);

    m_infoIOCoreScreen = new InfoIOCoreScreen(this);
    m_infoIODigitalScreen =  new InfoIODigitalScreen(this);
    m_infoIOAnalogScreen = new InfoIOAnalogScreen(this);
    m_infoIORTDScreen = new InfoIORTDScreen(this);

    m_infoIOCoreScreen->move(0, 41);
    m_infoIODigitalScreen->move(0, 41);
    m_infoIOAnalogScreen->move(0, 41);
    m_infoIORTDScreen->move(0, 41);

    m_infoIOCoreScreen->setVisible(true);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

    QObject::connect(ui->coreButton, SIGNAL(clicked()), this, SLOT(coreButtonCLicked()));
    QObject::connect(ui->digitalButton, SIGNAL(clicked()), this, SLOT(digitalButtonClicked()));
    QObject::connect(ui->analogButton, SIGNAL(clicked()), this, SLOT(analogButtonClicked()));
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
    m_infoIOAnalogScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

//    ui->coreButton->setDown(true);
//    ui->digitalButton->setDown(false);
//    ui->analogButton->setDown(false);
//    ui->rtdButton->setDown(false);
}

void InfoIOScreen::digitalButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(true);
    m_infoIOAnalogScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(false);

//    ui->coreButton->setDown(false);
//    ui->digitalButton->setDown(true);
//    ui->analogButton->setDown(false);
//    ui->rtdButton->setDown(false);
}

void InfoIOScreen::analogButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogScreen->setVisible(true);
    m_infoIORTDScreen->setVisible(false);

//    ui->coreButton->setDown(false);
//    ui->digitalButton->setDown(false);
//    ui->analogButton->setDown(true);
//    ui->rtdButton->setDown(false);
}

void InfoIOScreen::rtdButtonClicked()
{

    m_infoIOCoreScreen->setVisible(false);
    m_infoIODigitalScreen->setVisible(false);
    m_infoIOAnalogScreen->setVisible(false);
    m_infoIORTDScreen->setVisible(true);

//    ui->coreButton->setDown(false);
//    ui->digitalButton->setDown(false);
//    ui->analogButton->setDown(false);
//    ui->rtdButton->setDown(true);
}
