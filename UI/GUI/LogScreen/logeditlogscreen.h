#ifndef LOGEDITLOGSCREEN_H
#define LOGEDITLOGSCREEN_H

#include <QWidget>

namespace Ui {
class LogEditLogScreen;
}

class LogEditLogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LogEditLogScreen(QWidget *parent = 0);
    ~LogEditLogScreen();

private:
    Ui::LogEditLogScreen *ui;
};

#endif // LOGEDITLOGSCREEN_H
