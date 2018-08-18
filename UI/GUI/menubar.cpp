#include "menubar.h"
#include "ui_menubar.h"

MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuBar)
{
    ui->setupUi(this);

    QObject::connect(ui->homeButton, SIGNAL(pressed()), this, SLOT(on_homeButtonPressed()));
    QObject::connect(ui->infoButton, SIGNAL(pressed()), this, SLOT(on_infoButtonPressed()));
    QObject::connect(ui->startAPrintButton, SIGNAL(pressed()), this, SLOT(on_startAPrintButtonPressed()));
    QObject::connect(ui->logButton, SIGNAL(pressed()), this, SLOT(on_logButtonPressed()));
    QObject::connect(ui->settingsButton, SIGNAL(pressed()), this, SLOT(on_settingsButtonPressed()));
    QObject::connect(ui->sysActionsButton, SIGNAL(pressed()), this, SLOT(on_sysActionsButtonPressed()));
}

MenuBar::~MenuBar()
{
    delete ui;
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
