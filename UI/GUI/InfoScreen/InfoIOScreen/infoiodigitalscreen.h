#ifndef INFOIODIGITALSCREEN_H
#define INFOIODIGITALSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIODigitalScreen;
}

class InfoIODigitalScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIODigitalScreen(QWidget *parent = 0);
    ~InfoIODigitalScreen();

private:
    Ui::InfoIODigitalScreen *ui;
};

#endif // INFOIODIGITALSCREEN_H
