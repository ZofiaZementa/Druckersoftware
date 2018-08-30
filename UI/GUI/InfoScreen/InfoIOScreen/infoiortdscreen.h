#ifndef INFOIORTDSCREEN_H
#define INFOIORTDSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIORTDScreen;
}

class InfoIORTDScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIORTDScreen(QWidget *parent = 0);
    ~InfoIORTDScreen();

private:
    Ui::InfoIORTDScreen *ui;
};

#endif // INFOIORTDSCREEN_H
