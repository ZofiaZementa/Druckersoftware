#ifndef SYSACTIONSSCREEN_H
#define SYSACTIONSSCREEN_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class SysActionsScreen;
}

class SysActionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SysActionsScreen(QWidget *parent = 0);
    ~SysActionsScreen();

signals:

    void minimiseGUI();
    void closeSoftware();

private slots:

    void shutdownButtonClicked();
    void restartButtonClicked();
    void closeSoftwareButtonClicked();
    void minimiseButtonClicked();

private:
    Ui::SysActionsScreen *ui;
};

#endif // SYSACTIONSSCREEN_H
