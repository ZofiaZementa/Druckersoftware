#ifndef INFOIOANALOGINSCREEN_H
#define INFOIOANALOGINSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIOAnalogInScreen;
}

class InfoIOAnalogInScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOAnalogInScreen(QWidget *parent = 0);
    ~InfoIOAnalogInScreen();

private:
    Ui::InfoIOAnalogInScreen *ui;
};

#endif // INFOIOANALOGINSCREEN_H
