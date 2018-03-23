#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "machinecontroller.h"

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}
