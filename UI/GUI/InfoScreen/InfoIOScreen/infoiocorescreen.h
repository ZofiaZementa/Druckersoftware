#ifndef INFOIOCORESCREEN_H
#define INFOIOCORESCREEN_H

#include <QWidget>

namespace Ui {
class InfoIOCoreScreen;
}

class InfoIOCoreScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoIOCoreScreen(QWidget *parent = 0);
    ~InfoIOCoreScreen();

private:
    Ui::InfoIOCoreScreen *ui;
};

#endif // INFOIOCORESCREEN_H
