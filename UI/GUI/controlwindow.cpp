#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "machinecontroller.h"
#include <QMessageBox>


ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(QString(":/Lato/Lato-Light.ttf"));

    QApplication::setFont(QFont(QString("Lato-Light"), 11, QFont::Normal, false));

    m_menuBar = new MenuBar(this);
    m_errorScreen = new ErrorScreen(this);
    m_warningBar = new WarningBar(this);
    m_homeScreen = new HomeScreen(this);
    m_infoScreen = new InfoScreen(this);
    m_startAPrintScreen = new StartAPrintScreen(this);
    m_manualScreen = new ManualScreen(this);
    m_logScreen = new LogScreen(this);
    m_settingsScreen = new SettingsScreen(this);
    m_sysActionsScreen = new SysActionsScreen(this);

    //m_warningBar->raise();

    uiSetup();

    QObject::connect(m_menuBar, SIGNAL(homeButtonClicked()), this, SLOT(homeButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(infoButtonClicked()), this, SLOT(infoButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(startAPrintButtonClicked()), this, SLOT(startAPrintButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(manualButtonClicked()), this, SLOT(manualButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(logButtonClicked()), this, SLOT(logButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(settingsButtonClicked()), this, SLOT(settingsButtonClicked()));
    QObject::connect(m_menuBar, SIGNAL(sysActionsButtonClicked()), this, SLOT(sysActionsButtonClicked()));
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
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::homeButtonClicked()
{

    m_homeScreen->setVisible(true);
    m_infoScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::infoButtonClicked()
{

    m_infoScreen->setVisible(true);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::startAPrintButtonClicked()
{

    m_infoScreen->setVisible(false);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(true);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::manualButtonClicked()
{

    m_infoScreen->setVisible(false);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(true);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::logButtonClicked()
{

    m_infoScreen->setVisible(false);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(true);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::settingsButtonClicked()
{

    m_infoScreen->setVisible(false);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(true);
    m_sysActionsScreen->setVisible(false);
}

void ControlWindow::sysActionsButtonClicked()
{

    m_infoScreen->setVisible(false);
    m_homeScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(true);
}

void ControlWindow::logEntryOccured(QString logMessage, int code)
{

    emit logEntry(logMessage, code);
}

void ControlWindow::errorOccured(QString errorMessage)
{

    emit error(errorMessage);
}

void ControlWindow::uiSetup()
{

    m_warningBar->move(0, 480);
    m_homeScreen->move(61, 0);
    m_infoScreen->move(61, 0);
    m_startAPrintScreen->move(61, 0);
    m_manualScreen->move(61, 0);
    m_logScreen->move(61, 0);
    m_settingsScreen->move(61, 0);
    m_sysActionsScreen->move(61, 0);

    m_errorScreen->setVisible(false);
    m_warningBar->setVisible(false);
    m_infoScreen->setVisible(false);
    m_startAPrintScreen->setVisible(false);
    m_manualScreen->setVisible(false);
    m_logScreen->setVisible(false);
    m_settingsScreen->setVisible(false);
    m_sysActionsScreen->setVisible(false);
}
