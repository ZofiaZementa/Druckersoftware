#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "UI/GUI/menubar.h"
#include "UI/GUI/errorscreen.h"
#include "UI/GUI/warningbar.h"
#include "UI/GUI/homescreen.h"
#include "UI/GUI/InfoScreen/infoscreen.h"

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
    void logButtonClicked();
    void settingsButtonClicked();
    void sysActionsButtonClicked();
    void logEntryOccured(QString logMessage, int code);
    void errorOccured(QString errorMessage);

private:
    Ui::ControlWindow *ui;

    MenuBar *m_menuBar;
    ErrorScreen *m_errorScreen;
    WarningBar *m_warningBar;
    HomeScreen *m_homeScreen;
    InfoScreen *m_infoScreen;
};

#endif // CONTROLWINDOW_H
