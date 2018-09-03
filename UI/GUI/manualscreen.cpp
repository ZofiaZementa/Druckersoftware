#include "manualscreen.h"
#include "ui_manualscreen.h"

ManualScreen::ManualScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualScreen)
{
    ui->setupUi(this);

    QObject::connect(ui->manualControlCheckBox, SIGNAL(toggled(bool)), this, SLOT(manualControlCheckBoxToggled(bool)));
}

ManualScreen::~ManualScreen()
{
    delete ui;
}

void ManualScreen::manualControlCheckBoxToggled(bool)
{

}

void ManualScreen::xAxisPositiveButtonClicked()
{

}

void ManualScreen::xAxisNegativeButtonClicked()
{

}

void ManualScreen::yAxisPositiveButtonClicked()
{

}

void ManualScreen::yAxisNegativeButtonClicked()
{

}

void ManualScreen::zAxisPositiveButtonClicked()
{

}

void ManualScreen::zAxisNegativeButtonClicked()
{

}

void ManualScreen::extruderPositiveButtonClicked()
{

}

void ManualScreen::extruderNegativeButtonClicked()
{

}

void ManualScreen::homeButtonClicked()
{

}
