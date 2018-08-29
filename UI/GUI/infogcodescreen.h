#ifndef INFOGCODESCREEN_H
#define INFOGCODESCREEN_H

#include <QWidget>

namespace Ui {
class InfoGCodeScreen;
}

class InfoGCodeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoGCodeScreen(QWidget *parent = 0);
    ~InfoGCodeScreen();

private:
    Ui::InfoGCodeScreen *ui;
};

#endif // INFOGCODESCREEN_H
