#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class SpinBox;
}

class SpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit SpinBox(QWidget *parent = 0);
    ~SpinBox();

    void paintEvent(QPaintEvent *pe);
    void resize(int w, int h);
    void resize(const QSize &s);
    qreal value();
    void setMaximum(qreal maximum);
    qreal maximum();
    void setMinimum(qreal minimum);
    qreal minimum();
    void setSingleStep(qreal step);
    qreal singleStep();
    void setPrefix(QString prefix);
    QString prefix();
    void setSuffix(QString suffix);
    QString suffix();
    void setDecimals(int decimals);
    int decimals();

public slots:

    void setValue(qreal value);
    void stepUp();
    void stepDown();

signals:

    void valueChanged(qreal value);
    void valueEdited(qreal value);

private slots:

    void upButtonClicked();
    void downButtonClicked();
    void valueLineEditingFinished();

private:

    void uiSetup();
    qreal checkValueLineText();
    qreal fixValue(qreal value);
    void updateValueLineText();

    Ui::SpinBox *ui;
    qreal *m_value;
    QString *m_prefix;
    QString *m_suffix;
    qreal *m_minimum;
    qreal *m_maximum;
    qreal *m_stepSize;
    int *m_decimals;
};

#endif // SPINBOX_H
