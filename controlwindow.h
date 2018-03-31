#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();

public slots:

    void displayErrorMessage(QString errorMessage);

private:
    Ui::ControlWindow *ui;
};

#endif // CONTROLWINDOW_H
