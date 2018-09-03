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

private slots:

    void manualControlCheckBoxToggled(bool);
    void xAxisPositiveButtonClicked();
    void xAxisNegativeButtonClicked();
    void yAxisPositiveButtonClicked();
    void yAxisNegativeButtonClicked();
    void zAxisPositiveButtonClicked();
    void zAxisNegativeButtonClicked();
    void extruderPositiveButtonClicked();
    void extruderNegativeButtonClicked();
    void homeButtonClicked();

private:
    Ui::ManualScreen *ui;
};

#endif // MANUALSCREEN_H
