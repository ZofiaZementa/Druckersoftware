#ifndef INFOIOANALOGOUTSCREEN_H
#define INFOIOANALOGOUTSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIOAnalogOutScreen;
}

class InfoIOAnalogOutScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOAnalogOutScreen(QWidget *parent = 0);
    ~InfoIOAnalogOutScreen();

private:
    Ui::InfoIOAnalogOutScreen *ui;
};

#endif // INFOIOANALOGOUTSCREEN_H
