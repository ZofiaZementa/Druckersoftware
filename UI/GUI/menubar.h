#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QtSvg/QSvgWidget>
#include <QPainter>

namespace Ui {
class MenuBar;
}

class MenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit MenuBar(QWidget *parent = nullptr);
    ~MenuBar();

    void paintEvent(QPaintEvent *pe);

public slots:

    void setNetworkStatus(int status);

signals:

    void homeButtonClicked();
    void infoButtonClicked();
    void startAPrintButtonClicked();
    void logButtonClicked();
    void settingsButtonClicked();
    void sysActionsButtonClicked();

private slots:

    void on_homeButtonClicked();
    void on_infoButtonClicked();
    void on_startAPrintButtonClicked();
    void on_logButtonClicked();
    void on_settingsButtonClicked();
    void on_sysActionsButtonClicked();

private:

    Ui::MenuBar *ui;
    QSvgWidget *m_networkStatus;
};

#endif // MENUBAR_H
