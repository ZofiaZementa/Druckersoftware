#include "menubar.h"
#include "ui_menubar.h"

MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuBar)
{
    ui->setupUi(this);

    m_networkStatus = new QSvgWidget(this);

    QObject::connect(ui->homeButton, SIGNAL(pressed()), this, SLOT(on_homeButtonPressed()));
    QObject::connect(ui->infoButton, SIGNAL(pressed()), this, SLOT(on_infoButtonPressed()));
    QObject::connect(ui->startAPrintButton, SIGNAL(pressed()), this, SLOT(on_startAPrintButtonPressed()));
    QObject::connect(ui->logButton, SIGNAL(pressed()), this, SLOT(on_logButtonPressed()));
    QObject::connect(ui->settingsButton, SIGNAL(pressed()), this, SLOT(on_settingsButtonPressed()));
    QObject::connect(ui->sysActionsButton, SIGNAL(pressed()), this, SLOT(on_sysActionsButtonPressed()));

    m_networkStatus->load(QString(":/Icons/UI/Icons/sharp-signal_cellular_null-24px.svg"));
    m_networkStatus->resize(20, 20);
    m_networkStatus->move(20, 324);
}

MenuBar::~MenuBar()
{
    delete ui;
}

void MenuBar::setNetworkStatus(int status)
{

    if(status == 0){

        m_networkStatus->load(QString(":/Icons/UI/Icons/sharp-signal_cellular_null-24px.svg"));
    }

    else if(status == 1){

        m_networkStatus->load(QString(":/Icons/UI/Icons/sharp-signal_cellular_4_bar-24px.svg"));
    }
}

void MenuBar::on_homeButtonPressed()
{

    emit homeButtonPressed();
}

void MenuBar::on_infoButtonPressed()
{

    emit infoButtonPressed();
}

void MenuBar::on_startAPrintButtonPressed()
{

    emit startAPrintButtonPressed();
}

void MenuBar::on_logButtonPressed()
{

    emit logButtonPressed();
}

void MenuBar::on_settingsButtonPressed()
{

    emit settingsButtonPressed();
}

void MenuBar::on_sysActionsButtonPressed()
{

    emit sysActionsButtonPressed();
}
