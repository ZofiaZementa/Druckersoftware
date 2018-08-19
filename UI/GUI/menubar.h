#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QtSvg/QSvgWidget>

namespace Ui {
class MenuBar;
}

class MenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr);
    ~MenuBar();

public slots:

    void setNetworkStatus(int status);

signals:

    void homeButtonPressed();
    void infoButtonPressed();
    void startAPrintButtonPressed();
    void logButtonPressed();
    void settingsButtonPressed();
    void sysActionsButtonPressed();

private slots:

    void on_homeButtonPressed();
    void on_infoButtonPressed();
    void on_startAPrintButtonPressed();
    void on_logButtonPressed();
    void on_settingsButtonPressed();
    void on_sysActionsButtonPressed();

private:
    Ui::MenuBar *ui;

    QSvgWidget *m_networkStatus;
};

#endif // MENUBAR_H
