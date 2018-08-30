#ifndef INFOMISCSCREEN_H
#define INFOMISCSCREEN_H

#include <QWidget>

namespace Ui {
class InfoMiscScreen;
}

class InfoMiscScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoMiscScreen(QWidget *parent = 0);
    ~InfoMiscScreen();

private:
    Ui::InfoMiscScreen *ui;
};

#endif // INFOMISCSCREEN_H
