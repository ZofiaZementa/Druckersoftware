#include "menubar.h"
#include "ui_menubar.h"

MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuBar)
{
    ui->setupUi(this);

    m_networkStatus = new QSvgWidget(this);

    uiSetup();

    QObject::connect(ui->homeButton, SIGNAL(clicked()), this, SLOT(on_homeButtonClicked()));
    QObject::connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(on_infoButtonClicked()));
    QObject::connect(ui->startAPrintButton, SIGNAL(clicked()), this, SLOT(on_startAPrintButtonClicked()));
    QObject::connect(ui->manualButton, SIGNAL(clicked()), this, SLOT(on_manualButtonClicked()));
    QObject::connect(ui->logButton, SIGNAL(clicked()), this, SLOT(on_logButtonClicked()));
    QObject::connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(on_settingsButtonClicked()));
    QObject::connect(ui->sysActionsButton, SIGNAL(clicked()), this, SLOT(on_sysActionsButtonClicked()));
}

MenuBar::~MenuBar()
{
    delete ui;
}

void MenuBar::paintEvent(QPaintEvent *pe){

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
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

void MenuBar::on_homeButtonClicked()
{

    emit homeButtonClicked();

    ui->homeButton->setChecked(true);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_infoButtonClicked()
{

    emit infoButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(true);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_startAPrintButtonClicked()
{

    emit startAPrintButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(true);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_manualButtonClicked()
{

    emit manualButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(true);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_logButtonClicked()
{

    emit logButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(true);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_settingsButtonClicked()
{

    emit settingsButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(true);
    ui->sysActionsButton->setChecked(false);
}

void MenuBar::on_sysActionsButtonClicked()
{

    emit sysActionsButtonClicked();

    ui->homeButton->setChecked(false);
    ui->infoButton->setChecked(false);
    ui->startAPrintButton->setChecked(false);
    ui->manualButton->setChecked(false);
    ui->logButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    ui->sysActionsButton->setChecked(true);
}

void MenuBar::uiSetup()
{

    ui->homeButton->setCheckable(true);
    ui->infoButton->setCheckable(true);
    ui->startAPrintButton->setCheckable(true);
    ui->manualButton->setCheckable(true);
    ui->logButton->setCheckable(true);
    ui->settingsButton->setCheckable(true);
    ui->sysActionsButton->setCheckable(true);

    ui->homeButton->setChecked(true);

    m_networkStatus->load(QString(":/Icons/UI/Icons/sharp-signal_cellular_null-24px.svg"));
    m_networkStatus->resize(20, 20);
    m_networkStatus->move(20, 385);
}
