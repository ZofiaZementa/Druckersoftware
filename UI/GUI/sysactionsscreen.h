#ifndef SYSACTIONSSCREEN_H
#define SYSACTIONSSCREEN_H

#include <QWidget>

namespace Ui {
class SysActionsScreen;
}

class SysActionsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SysActionsScreen(QWidget *parent = 0);
    ~SysActionsScreen();

private:
    Ui::SysActionsScreen *ui;
};

#endif // SYSACTIONSSCREEN_H
