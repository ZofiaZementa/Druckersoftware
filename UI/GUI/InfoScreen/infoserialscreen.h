#ifndef INFOSERIALSCREEN_H
#define INFOSERIALSCREEN_H

#include <QWidget>

namespace Ui {
class InfoSerialScreen;
}

class InfoSerialScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoSerialScreen(QWidget *parent = 0);
    ~InfoSerialScreen();

private:
    Ui::InfoSerialScreen *ui;
};

#endif // INFOSERIALSCREEN_H
