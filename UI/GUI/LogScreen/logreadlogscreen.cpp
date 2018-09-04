#include "logreadlogscreen.h"
#include "ui_logreadlogscreen.h"

LogReadLogScreen::LogReadLogScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogReadLogScreen)
{
    ui->setupUi(this);
}

LogReadLogScreen::~LogReadLogScreen()
{
    delete ui;
}
