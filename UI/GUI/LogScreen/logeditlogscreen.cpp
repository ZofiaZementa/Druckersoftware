#include "logeditlogscreen.h"
#include "ui_logeditlogscreen.h"

LogEditLogScreen::LogEditLogScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogEditLogScreen)
{
    ui->setupUi(this);
}

LogEditLogScreen::~LogEditLogScreen()
{
    delete ui;
}
