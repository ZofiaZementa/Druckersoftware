#ifndef INFOGENERALSCREEN_H
#define INFOGENERALSCREEN_H

#include <QWidget>

namespace Ui {
class InfoGeneralScreen;
}

class InfoGeneralScreen : public QWidget
{
    Q_OBJECT

public:
    explicit InfoGeneralScreen(QWidget *parent = 0);
    ~InfoGeneralScreen();

private:
    Ui::InfoGeneralScreen *ui;
};

#endif // INFOGENERALSCREEN_H
