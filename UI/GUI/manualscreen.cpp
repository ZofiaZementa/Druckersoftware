#include "manualscreen.h"
#include "ui_manualscreen.h"

ManualScreen::ManualScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualScreen)
{
    ui->setupUi(this);
}

ManualScreen::~ManualScreen()
{
    delete ui;
}
