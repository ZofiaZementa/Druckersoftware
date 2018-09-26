#ifndef WARNINGBAR_H
#define WARNINGBAR_H

#include <QWidget>
#include <QtSvg/QSvgWidget>
#include <QPainter>
#include <QStyleOption>

namespace Ui {
class WarningBar;
}

class WarningBar : public QWidget
{
    Q_OBJECT

public:
    explicit WarningBar(QWidget *parent = 0);
    ~WarningBar();

    void paintEvent(QPaintEvent *pe);

public slots:

    void showWarning(QString warningMsg);

signals:

    void okButtonClicked();

private slots:

    void on_okButtonClicked();

private:
    Ui::WarningBar *ui;

    QSvgWidget *m_warningIcon;
};

#endif // WARNINGBAR_H
