#ifndef ERRORSCREEN_H
#define ERRORSCREEN_H

#include <QWidget>
#include <QtSvg/QSvgWidget>
#include <QPainter>

namespace Ui {
class ErrorScreen;
}

class ErrorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorScreen(QWidget *parent = 0);
    ~ErrorScreen();

    void paintEvent(QPaintEvent *pe);

public slots:

    void showError(int code, QString message);

signals:

    void okButtonClicked();

private slots:

    void on_okButtonClicked();

private:

    QString convertDecToHex(int decimal);

    Ui::ErrorScreen *ui;

    QSvgWidget *m_errorIcon;
};

#endif // ERRORSCREEN_H
