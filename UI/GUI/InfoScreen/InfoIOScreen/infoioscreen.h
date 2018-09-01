#ifndef INFOIOSCREEN_H
#define INFOIOSCREEN_H

#include <QWidget>
#include "UI/GUI/InfoScreen/InfoIOScreen/infoiocorescreen.h"
#include "UI/GUI/InfoScreen/InfoIOScreen/infoiodigitalscreen.h"
#include "UI/GUI/InfoScreen/InfoIOScreen/infoioanalogoutscreen.h"
#include "UI/GUI/InfoScreen/InfoIOScreen/infoioanaloginscreen.h"
#include "UI/GUI/InfoScreen/InfoIOScreen/infoiortdscreen.h"

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
    void analogOutButtonClicked();
    void analogInButtonClicked();
    void rtdButtonClicked();

private:

    Ui::InfoIOScreen *ui;
    InfoIOCoreScreen *m_infoIOCoreScreen;
    InfoIODigitalScreen *m_infoIODigitalScreen;
    InfoIOAnalogOutScreen *m_infoIOAnalogOutScreen;
    InfoIOAnalogInScreen *m_infoIOAnalogInScreen;
    InfoIORTDScreen *m_infoIORTDScreen;
};

#endif // INFOIOSCREEN_H
