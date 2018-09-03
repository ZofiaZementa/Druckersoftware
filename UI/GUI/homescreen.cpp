#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    ui->xValueLabel->setReadOnly(true);
    ui->yValueLabel->setReadOnly(true);
    ui->zValueLabel->setReadOnly(true);
    ui->eValueLabel->setReadOnly(true);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}
