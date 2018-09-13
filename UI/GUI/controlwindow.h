#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include "UI/GUI/menubar.h"
#include "UI/GUI/errorscreen.h"
#include "UI/GUI/warningbar.h"
#include "UI/GUI/homescreen.h"
#include "UI/GUI/InfoScreen/infoscreen.h"
#include "UI/GUI/startaprintscreen.h"
#include "UI/GUI/manualscreen.h"
#include "UI/GUI/LogScreen/logscreen.h"
#include "UI/GUI/SettingsScreen/settingsscreen.h"
#include "UI/GUI/sysactionsscreen.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

public slots:

    void displayErrorMessage(QString errorMessage);
    void displayErrorMessage(int code, QString errorMessage);

signals:

    void closed();
    void logEntry(QString logMessage, int code);
    void error(QString errorMessage);

private slots:

    void errorScreenOKButtonClicked();
    void homeButtonClicked();
    void infoButtonClicked();
    void startAPrintButtonClicked();
    void manualButtonClicked();
    void logButtonClicked();
    void settingsButtonClicked();
    void sysActionsButtonClicked();
    void logEntryOccured(QString logMessage, int code);
    void errorOccured(QString errorMessage);

private:

    void uiSetup();

    Ui::ControlWindow *ui;
    MenuBar *m_menuBar;
    ErrorScreen *m_errorScreen;
    WarningBar *m_warningBar;
    HomeScreen *m_homeScreen;
    InfoScreen *m_infoScreen;
    StartAPrintScreen *m_startAPrintScreen;
    ManualScreen *m_manualScreen;
    LogScreen *m_logScreen;
    SettingsScreen *m_settingsScreen;
    SysActionsScreen *m_sysActionsScreen;
};

#endif // CONTROLWINDOW_H
