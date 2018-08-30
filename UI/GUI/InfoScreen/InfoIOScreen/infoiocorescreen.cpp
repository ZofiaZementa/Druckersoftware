#include "infoiocorescreen.h"
#include "ui_infoiocorescreen.h"

InfoIOCoreScreen::InfoIOCoreScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOCoreScreen)
{
    ui->setupUi(this);
}

InfoIOCoreScreen::~InfoIOCoreScreen()
{
    delete ui;
}
