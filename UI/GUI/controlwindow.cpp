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
    m_errorScreen = new ErrorScreen(this);
    m_warningBar = new WarningBar(this);
    m_homeScreen = new HomeScreen(this);
    m_infoScreen = new InfoScreen(this);

    m_homeScreen->move(61, 0);
    m_infoScreen->move(61, 0);
    m_warningBar->move(0, 480);

    m_errorScreen->setVisible(false);
    m_warningBar->setVisible(false);
    m_infoScreen->setVisible(false);

    //m_warningBar->raise();

    QObject::connect(m_menuBar, SIGNAL(homeButtonClicked()), this, SLOT(homeButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(infoButtonClicked()), this, SLOT(infoButtonClicked()));
    QObject::connect(m_errorScreen, SIGNAL(okButtonClicked()), this, SLOT(errorScreenOKButtonClicked()));
}

ControlWindow::~ControlWindow()
{
    delete ui;

    emit closed();
}

void ControlWindow::displayErrorMessage(QString errorMessage)
{

    m_menuBar->setVisible(false);
    m_errorScreen->setVisible(true);
    m_homeScreen->setVisible(false);
    m_infoScreen->setVisible(false);
    m_errorScreen->showError(0, errorMessage);
}

void ControlWindow::displayErrorMessage(int code, QString errorMessage)
{

    m_errorScreen->showError(code, errorMessage);
}

void ControlWindow::errorScreenOKButtonClicked()
{

    m_menuBar->setVisible(true);
    m_errorScreen->setVisible(false);
    m_homeScreen->setVisible(true);
    m_infoScreen->setVisible(false);
}

void ControlWindow::homeButtonClicked()
{

    m_homeScreen->setVisible(true);
    m_infoScreen->setVisible(false);
}

void ControlWindow::infoButtonClicked()
{

    m_infoScreen->setVisible(true);
    m_homeScreen->setVisible(false);
}

void ControlWindow::startAPrintButtonClicked()
{

}

void ControlWindow::logButtonClicked()
{

}

void ControlWindow::settingsButtonClicked()
{

}

void ControlWindow::sysActionsButtonClicked()
{

}

void ControlWindow::logEntryOccured(QString logMessage, int code)
{

    emit logEntry(logMessage, code);
}

void ControlWindow::errorOccured(QString errorMessage)
{

    emit error(errorMessage);
}
