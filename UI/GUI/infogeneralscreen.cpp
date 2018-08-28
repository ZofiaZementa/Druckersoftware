#include "infogeneralscreen.h"
#include "ui_infogeneralscreen.h"

InfoGeneralScreen::InfoGeneralScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoGeneralScreen)
{
    ui->setupUi(this);
}

InfoGeneralScreen::~InfoGeneralScreen()
{
    delete ui;
}
