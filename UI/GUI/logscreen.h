#ifndef LOGSCREEN_H
#define LOGSCREEN_H

#include <QWidget>
#include "spinbox.h"

namespace Ui {
class LogScreen;
}

class LogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LogScreen(QWidget *parent = 0);
    ~LogScreen();

private:
    Ui::LogScreen *ui;
};

#endif // LOGSCREEN_H
