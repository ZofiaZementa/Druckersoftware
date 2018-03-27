#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "machinecontroller.h"

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    MachineController test;
}

ControlWindow::~ControlWindow()
{
    delete ui;
}
