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
