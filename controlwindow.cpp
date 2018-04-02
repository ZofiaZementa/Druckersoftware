#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "machinecontroller.h"
#include <QMessageBox>

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

void ControlWindow::displayErrorMessage(QString errorMessage)
{

    QMessageBox errorBox;

    errorBox.setText(QString("Error: ").append(errorMessage).append(QString("!")));
    errorBox.setIcon(QMessageBox::Critical);
    errorBox.addButton(QMessageBox::Ok);
    errorBox.setDefaultButton(QMessageBox::Ok);
    errorBox.setWindowTitle(QString("ERROR"));
    errorBox.exec();
}
