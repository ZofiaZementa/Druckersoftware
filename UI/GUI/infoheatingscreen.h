#ifndef INFOHEATINGSCREEN_H
#define INFOHEATINGSCREEN_H

#include <QWidget>

namespace Ui {
class InfoHeatingScreen;
}

class InfoHeatingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoHeatingScreen(QWidget *parent = 0);
    ~InfoHeatingScreen();

private:
    Ui::InfoHeatingScreen *ui;
};

#endif // INFOHEATINGSCREEN_H
