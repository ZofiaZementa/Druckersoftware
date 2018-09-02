#ifndef MANUALSCREEN_H
#define MANUALSCREEN_H

#include <QWidget>

namespace Ui {
class ManualScreen;
}

class ManualScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ManualScreen(QWidget *parent = 0);
    ~ManualScreen();

private:
    Ui::ManualScreen *ui;
};

#endif // MANUALSCREEN_H
