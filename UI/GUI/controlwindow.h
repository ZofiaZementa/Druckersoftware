#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "UI/GUI/menubar.h"

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
};

#endif // CONTROLWINDOW_H
