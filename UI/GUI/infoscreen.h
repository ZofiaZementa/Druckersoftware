#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include <QWidget>

namespace Ui {
class InfoScreen;
}

class InfoScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoScreen(QWidget *parent = 0);
    ~InfoScreen();

private:
    Ui::InfoScreen *ui;
};

#endif // INFOSCREEN_H
