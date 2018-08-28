#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include <QWidget>
#include "infogeneralscreen.h"
#include "infomotorscreen.h"
#include "infoheatingscreen.h"
#include "infoioscreen.h"
#include "infoserialscreen.h"
#include "infomiscscreen.h"

namespace Ui {
class InfoScreen;
}

class InfoScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoScreen(QWidget *parent = 0);
    ~InfoScreen();

private slots:

    void generalButtonClicked();
    void motorButtonClicked();
    void heatingButtonClicked();
    void ioButtonClicked();
    void serialButtonClicked();
    void miscButtonClicked();

private:

    Ui::InfoScreen *ui;
    InfoGeneralScreen *m_infoGeneralScreen;
    InfoMotorScreen *m_infoMotorScreen;
    InfoHeatingScreen *m_infoHeatingScreen;
    InfoIOScreen *m_infoIOScreen;
    InfoSerialScreen *m_infoSerialScreen;
    InfoMiscScreen *m_infoMiscScreen;
};

#endif // INFOSCREEN_H
