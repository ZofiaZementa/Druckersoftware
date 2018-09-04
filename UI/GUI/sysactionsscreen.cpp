#include "sysactionsscreen.h"
#include "ui_sysactionsscreen.h"

SysActionsScreen::SysActionsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysActionsScreen)
{
    ui->setupUi(this);
}

SysActionsScreen::~SysActionsScreen()
{
    delete ui;
}

void SysActionsScreen::shutdownButtonClicked()
{
    QStringList arguments;

    arguments.append(QString("-P"));
    arguments.append(QString("now"));
    QProcess::execute(QString("shutdown"), arguments);
}

void SysActionsScreen::restartButtonClicked()
{

    QStringList arguments;

    arguments.append(QString("-r"));
    arguments.append(QString("now"));
    QProcess::execute(QString("shutdown"), arguments);
}

void SysActionsScreen::closeSoftwareButtonClicked()
{

    emit closeSoftware();
}

void SysActionsScreen::minimiseButtonClicked()
{

    emit minimiseGUI();
}
