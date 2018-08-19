#include "infoscreen.h"
#include "ui_infoscreen.h"

InfoScreen::InfoScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoScreen)
{
    ui->setupUi(this);
}

InfoScreen::~InfoScreen()
{
    delete ui;
}
