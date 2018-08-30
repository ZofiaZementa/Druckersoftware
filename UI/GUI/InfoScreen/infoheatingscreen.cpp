#include "infoheatingscreen.h"
#include "ui_infoheatingscreen.h"

InfoHeatingScreen::InfoHeatingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoHeatingScreen)
{
    ui->setupUi(this);
}

InfoHeatingScreen::~InfoHeatingScreen()
{
    delete ui;
}
