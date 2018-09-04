#ifndef LOGREADLOGSCREEN_H
#define LOGREADLOGSCREEN_H

#include <QWidget>

namespace Ui {
class LogReadLogScreen;
}

class LogReadLogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LogReadLogScreen(QWidget *parent = 0);
    ~LogReadLogScreen();

private:
    Ui::LogReadLogScreen *ui;
};

#endif // LOGREADLOGSCREEN_H
