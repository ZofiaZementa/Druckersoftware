#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "UI/GUI/menubar.h"
#include "UI/GUI/homescreen.h"
#include "UI/GUI/infoscreen.h"

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

signals:

    void closed();

private slots:

    void homeButtonPressed();
    void infoButtonPressed();
    void startAPrintButtonPressed();
    void logButtonPressed();
    void settingsButtonPressed();
    void sysActionsButtonPressed();

private:
    Ui::ControlWindow *ui;

    MenuBar *m_menuBar;
    HomeScreen *m_homeScreen;
    InfoScreen *m_infoScreen;
};

#endif // CONTROLWINDOW_H
