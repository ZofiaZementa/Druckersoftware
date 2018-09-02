#ifndef STARTAPRINTSCREEN_H
#define STARTAPRINTSCREEN_H

#include <QWidget>

namespace Ui {
class StartAPrintScreen;
}

class StartAPrintScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartAPrintScreen(QWidget *parent = 0);
    ~StartAPrintScreen();

private:
    Ui::StartAPrintScreen *ui;
};

#endif // STARTAPRINTSCREEN_H
