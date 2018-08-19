#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "machinecontroller.h"
#include <QMessageBox>


ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    m_menuBar = new MenuBar(this);
    m_homeScreen = new HomeScreen(this);
    m_infoScreen = new InfoScreen(this);

    m_menuBar->move(0, 0);
    m_homeScreen->move(61, 0);
    m_infoScreen->move(61, 0);
    m_homeScreen->setVisible(false);


    //QObject::connect(m_menuBar, SIGNAL(home), this, SLOT(on_homeButtonPressed()));
}

ControlWindow::~ControlWindow()
{
    delete ui;

    emit closed();
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

void ControlWindow::homeButtonPressed()
{

}

void ControlWindow::infoButtonPressed()
{

}

void ControlWindow::startAPrintButtonPressed()
{

}

void ControlWindow::logButtonPressed()
{

}

void ControlWindow::settingsButtonPressed()
{

}

void ControlWindow::sysActionsButtonPressed()
{

}
