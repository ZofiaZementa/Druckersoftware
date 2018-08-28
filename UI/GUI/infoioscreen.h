#ifndef INFOIOSCREEN_H
#define INFOIOSCREEN_H

#include <QWidget>

namespace Ui {
class InfoIOScreen;
}

class InfoIOScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOScreen(QWidget *parent = 0);
    ~InfoIOScreen();

private:
    Ui::InfoIOScreen *ui;
};

#endif // INFOIOSCREEN_H
