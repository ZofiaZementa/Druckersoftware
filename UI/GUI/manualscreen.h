#ifndef MANUALSCREEN_H
#define MANUALSCREEN_H

#include <QWidget>
#include <QSettings>
#include "UI/GUI/spinbox.h"

namespace Ui {
class ManualScreen;
}

class ManualScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ManualScreen(QWidget *parent = 0);
    ~ManualScreen();

public slots:

    void setXSpinBoxValue(qreal value);
    void setYSpinBoxValue(qreal value);
    void setZSpinBoxValue(qreal value);
    void setESpinBoxValue(qreal value);
    void setHotEndTargetTempSpinBoxValue(qreal value);
    void setBedTargetTempSpinBoxValue(qreal value);

signals:

    void relativeMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed);
    void absoluteMove(qreal x, qreal y, qreal z, qreal e, qreal xSpeed, qreal ySpeed, qreal zSpeed, qreal eSpeed);
    void g28(bool x, bool y, bool z);
    void m104(int s);
    void m140(int s);
    void gCodeCommand(QString command);
    void setManualControl(bool on);

private slots:

    void manualControlCheckBoxToggled(bool on);
    void xAxisPositiveButtonClicked();
    void xAxisNegativeButtonClicked();
    void yAxisPositiveButtonClicked();
    void yAxisNegativeButtonClicked();
    void zAxisPositiveButtonClicked();
    void zAxisNegativeButtonClicked();
    void extruderPositiveButtonClicked();
    void extruderNegativeButtonClicked();
    void homeButtonClicked();
    void gcodeExecuteButtonClicked();
    void stepsPerClickSpinBoxValueEdited(qreal value);
    void xSpinBoxValueEdited(qreal value);
    void ySpinBoxValueEdited(qreal value);
    void zSpinBoxValueEdited(qreal value);
    void eSpinBoxValueEdited(qreal value);
    void hotEndTargetTempSpinBoxValueEdited(qreal value);
    void bedTargetTempSpinBoxEdited(qreal value);

private:

    void uiSetup();
    void uiUpdateSettings();
    void uiUpdateValues();

    Ui::ManualScreen *ui;
    SpinBox *fSpinBox;
    SpinBox *stepsPerClickSpinBox;
    SpinBox *xSpinBox;
    SpinBox *ySpinBox;
    SpinBox *zSpinBox;
    SpinBox *eSpinBox;
    SpinBox *hotEndTargetTempSpinBox;
    SpinBox *bedTargetTempSpinBox;
    QSettings *m_settings;
};

#endif // MANUALSCREEN_H
