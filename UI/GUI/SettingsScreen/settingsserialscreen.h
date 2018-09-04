#ifndef SETTINGSSERIALSCREEN_H
#define SETTINGSSERIALSCREEN_H

#include <QWidget>

namespace Ui {
class SettingsSerialScreen;
}

class SettingsSerialScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsSerialScreen(QWidget *parent = 0);
    ~SettingsSerialScreen();

private:
    Ui::SettingsSerialScreen *ui;
};

#endif // SETTINGSSERIALSCREEN_H
