#include "infoserialscreen.h"
#include "ui_infoserialscreen.h"

InfoSerialScreen::InfoSerialScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoSerialScreen)
{
    ui->setupUi(this);
}

InfoSerialScreen::~InfoSerialScreen()
{
    delete ui;
}
