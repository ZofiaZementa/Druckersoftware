#include "startaprintscreen.h"
#include "ui_startaprintscreen.h"

StartAPrintScreen::StartAPrintScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartAPrintScreen)
{
    ui->setupUi(this);
}

StartAPrintScreen::~StartAPrintScreen()
{
    delete ui;
}
