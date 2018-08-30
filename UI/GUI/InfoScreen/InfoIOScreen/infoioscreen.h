#ifndef INFOIOSCREEN_H
#define INFOIOSCREEN_H

#include <QWidget>
#include "infoiocorescreen.h"
#include "infoiodigitalscreen.h"
#include "infoioanalogscreen.h"
#include "infoiortdscreen.h"

namespace Ui {
class InfoIOScreen;
}

class InfoIOScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOScreen(QWidget *parent = 0);
    ~InfoIOScreen();

private slots:

    void coreButtonCLicked();
    void digitalButtonClicked();
    void analogButtonClicked();
    void rtdButtonClicked();

private:
    Ui::InfoIOScreen *ui;

    InfoIOCoreScreen *m_infoIOCoreScreen;
    InfoIODigitalScreen *m_infoIODigitalScreen;
    InfoIOAnalogScreen *m_infoIOAnalogScreen;
    InfoIORTDScreen *m_infoIORTDScreen;
};

#endif // INFOIOSCREEN_H
