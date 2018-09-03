#include "logscreen.h"
#include "ui_logscreen.h"

LogScreen::LogScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogScreen)
{
    ui->setupUi(this);
}

LogScreen::~LogScreen()
{
    delete ui;
}

