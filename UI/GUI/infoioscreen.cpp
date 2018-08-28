#include "infoioscreen.h"
#include "ui_infoioscreen.h"

InfoIOScreen::InfoIOScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoIOScreen)
{
    ui->setupUi(this);
}

InfoIOScreen::~InfoIOScreen()
{
    delete ui;
}
