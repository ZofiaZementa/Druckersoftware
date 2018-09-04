#include "logscreen.h"
#include "ui_logscreen.h"

LogScreen::LogScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogScreen)
{
    ui->setupUi(this);

    m_logEditLogScreen = new LogEditLogScreen(this);
    m_logReadLogScreen = new LogReadLogScreen(this);

    m_logEditLogScreen->move(0, 41);
    m_logReadLogScreen->move(0, 41);

    m_logReadLogScreen->setVisible(false);

    ui->editLogButton->setChecked(true);

    QObject::connect(ui->editLogButton, SIGNAL(clicked()), this, SLOT(editLogButtonClicked()));
    QObject::connect(ui->readLogButton, SIGNAL(clicked()), this, SLOT(readLogButtonClicked()));
}

LogScreen::~LogScreen()
{
    delete ui;
}

void LogScreen::editLogButtonClicked()
{

    m_logEditLogScreen->setVisible(true);
    m_logReadLogScreen->setVisible(false);

    ui->editLogButton->setChecked(true);
    ui->readLogButton->setChecked(false);
}

void LogScreen::readLogButtonClicked()
{

    m_logEditLogScreen->setVisible(false);
    m_logReadLogScreen->setVisible(true);

    ui->editLogButton->setChecked(false);
    ui->readLogButton->setChecked(true);
}

