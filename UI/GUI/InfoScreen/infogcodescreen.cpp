#include "infogcodescreen.h"
#include "ui_infogcodescreen.h"

InfoGCodeScreen::InfoGCodeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoGCodeScreen)
{
    ui->setupUi(this);
}

InfoGCodeScreen::~InfoGCodeScreen()
{
    delete ui;
}
