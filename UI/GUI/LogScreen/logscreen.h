#ifndef LOGSCREEN_H
#define LOGSCREEN_H

#include <QWidget>
#include "UI/GUI/LogScreen/logeditlogscreen.h"
#include "UI/GUI/LogScreen/logreadlogscreen.h"

namespace Ui {
class LogScreen;
}

class LogScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LogScreen(QWidget *parent = 0);
    ~LogScreen();

private slots:

    void editLogButtonClicked();
    void readLogButtonClicked();

private:

    Ui::LogScreen *ui;
    LogEditLogScreen *m_logEditLogScreen;
    LogReadLogScreen *m_logReadLogScreen;
};

#endif // LOGSCREEN_H
