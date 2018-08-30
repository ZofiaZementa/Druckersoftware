#ifndef INFOMOTORSCREEN_H
#define INFOMOTORSCREEN_H

#include <QWidget>

namespace Ui {
class InfoMotorScreen;
}

class InfoMotorScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoMotorScreen(QWidget *parent = 0);
    ~InfoMotorScreen();

private:
    Ui::InfoMotorScreen *ui;
};

#endif // INFOMOTORSCREEN_H
