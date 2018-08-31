#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "UI/GUI/menubar.h"
#include "UI/GUI/errorscreen.h"
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

private slots:

    void errorScreenOKButtonClicked();
    void homeButtonClicked();
    void infoButtonClicked();
    void startAPrintButtonClicked();
    void logButtonClicked();
    void settingsButtonClicked();
    void sysActionsButtonClicked();

private:
    Ui::ControlWindow *ui;

    MenuBar *m_menuBar;
    ErrorScreen *m_errorScreen;
    HomeScreen *m_homeScreen;
    InfoScreen *m_infoScreen;
};

#endif // CONTROLWINDOW_H
