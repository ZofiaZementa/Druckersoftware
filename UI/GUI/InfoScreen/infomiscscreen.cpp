#include "infomiscscreen.h"
#include "ui_infomiscscreen.h"

InfoMiscScreen::InfoMiscScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoMiscScreen)
{
    ui->setupUi(this);
}

InfoMiscScreen::~InfoMiscScreen()
{
    delete ui;
}
