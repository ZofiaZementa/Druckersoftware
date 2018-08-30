#ifndef INFOIOANALOGSCREEN_H
#define INFOIOANALOGSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIOAnalogScreen;
}

class InfoIOAnalogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOAnalogScreen(QWidget *parent = 0);
    ~InfoIOAnalogScreen();

private:
    Ui::InfoIOAnalogScreen *ui;
};

#endif // INFOIOANALOGSCREEN_H
