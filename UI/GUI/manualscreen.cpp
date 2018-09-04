#include "manualscreen.h"
#include "ui_manualscreen.h"

ManualScreen::ManualScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualScreen)
{
    ui->setupUi(this);

    fSpinBox = new SpinBox(this);
    stepsPerClickSpinBox = new SpinBox(this);
    xSpinBox = new SpinBox(this);
    ySpinBox = new SpinBox(this);
    zSpinBox = new SpinBox(this);
    eSpinBox = new SpinBox(this);
    hotEndTargetTempSpinBox = new SpinBox(this);
    bedTargetTempSpinBox = new SpinBox(this);
    m_settings = new QSettings(this);

    uiSetup();

    QObject::connect(ui->manualControlCheckBox, SIGNAL(toggled(bool)), this, SLOT(manualControlCheckBoxToggled(bool)));
    QObject::connect(ui->xAxisPositiveButton, SIGNAL(clicked()), this, SLOT(xAxisPositiveButtonClicked()));
    QObject::connect(ui->xAxisNegativeButton, SIGNAL(clicked()), this, SLOT(xAxisNegativeButtonClicked()));
    QObject::connect(ui->yAxisPositiveButton, SIGNAL(clicked()), this, SLOT(yAxisPositiveButtonClicked()));
    QObject::connect(ui->yAxisNegativeButton, SIGNAL(clicked()), this, SLOT(yAxisNegativeButtonClicked()));
    QObject::connect(ui->zAxisPositiveButton, SIGNAL(clicked()), this, SLOT(zAxisPositiveButtonClicked()));
    QObject::connect(ui->zAxisNegativeButton, SIGNAL(clicked()), this, SLOT(zAxisNegativeButtonClicked()));
    QObject::connect(ui->extruderPositiveButton, SIGNAL(clicked()), this, SLOT(extruderPositiveButtonClicked()));
    QObject::connect(ui->extruderNegativeButton, SIGNAL(clicked()), this, SLOT(extruderNegativeButtonClicked()));
    QObject::connect(ui->homeButton, SIGNAL(clicked()), this, SLOT(homeButtonClicked()));
    QObject::connect(ui->gcodeExecuteButton, SIGNAL(clicked()), this, SLOT(gcodeExecuteButtonClicked()));
    QObject::connect(stepsPerClickSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(stepsPerClickSpinBoxValueEdited(qreal)));
    QObject::connect(xSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(xSpinBoxValueEdited(qreal)));
    QObject::connect(ySpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(ySpinBoxValueEdited(qreal)));
    QObject::connect(zSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(zSpinBoxValueEdited(qreal)));
    QObject::connect(eSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(eSpinBoxValueEdited(qreal)));
    QObject::connect(hotEndTargetTempSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(hotEndTargetTempSpinBoxValueEdited(qreal)));
    QObject::connect(bedTargetTempSpinBox, SIGNAL(valueEdited(qreal)), this, SLOT(bedTargetTempSpinBoxEdited(qreal)));

    uiUpdateSettings();
    uiUpdateValues();
}

ManualScreen::~ManualScreen()
{
    delete ui;
}

void ManualScreen::setXSpinBoxValue(qreal value)
{

    xSpinBox->setValue(value);
}

void ManualScreen::setYSpinBoxValue(qreal value)
{

    ySpinBox->setValue(value);
}

void ManualScreen::setZSpinBoxValue(qreal value)
{

    zSpinBox->setValue(value);
}

void ManualScreen::setESpinBoxValue(qreal value)
{

    eSpinBox->setValue(value);
}

void ManualScreen::setHotEndTargetTempSpinBoxValue(qreal value)
{

    hotEndTargetTempSpinBox->setValue(value);
}

void ManualScreen::setBedTargetTempSpinBoxValue(qreal value)
{

    bedTargetTempSpinBox->setValue(value);
}

void ManualScreen::manualControlCheckBoxToggled(bool on)
{

    emit setManualControl(on);

    ui->xAxisPositiveButton->setEnabled(on);
    ui->xAxisNegativeButton->setEnabled(on);
    ui->yAxisPositiveButton->setEnabled(on);
    ui->yAxisNegativeButton->setEnabled(on);
    ui->zAxisPositiveButton->setEnabled(on);
    ui->zAxisNegativeButton->setEnabled(on);
    ui->extruderPositiveButton->setEnabled(on);
    ui->extruderNegativeButton->setEnabled(on);
    ui->homeButton->setEnabled(on);
    ui->gcodeExecuteButton->setEnabled(on);
    ui->gcodeLine->setEnabled(on);
    fSpinBox->setEnabled(on);
    stepsPerClickSpinBox->setEnabled(on);
    xSpinBox->setEnabled(on);
    ySpinBox->setEnabled(on);
    zSpinBox->setEnabled(on);
    eSpinBox->setEnabled(on);
    hotEndTargetTempSpinBox->setEnabled(on);
    bedTargetTempSpinBox->setEnabled(on);
}

void ManualScreen::xAxisPositiveButtonClicked()
{

    emit relativeMove(m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/xaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal(), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0, 0.0);
}

void ManualScreen::xAxisNegativeButtonClicked()
{

    emit relativeMove(m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/xaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal() * (-1.0), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0, 0.0);
}

void ManualScreen::yAxisPositiveButtonClicked()
{

    emit relativeMove(0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/yaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal(), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0);
}

void ManualScreen::yAxisNegativeButtonClicked()
{

    emit relativeMove(0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/yaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal() * (-1.0), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0);
}

void ManualScreen::zAxisPositiveButtonClicked()
{

    emit relativeMove(0.0, 0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/zaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal(), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0);
}

void ManualScreen::zAxisNegativeButtonClicked()
{

    emit relativeMove(0.0, 0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/zaxis/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal() * (-1.0), 0.0, 0.0, 0.0, fSpinBox->value(), 0.0);
}

void ManualScreen::extruderPositiveButtonClicked()
{

    emit relativeMove(0.0, 0.0, 0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/extruder/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal(), 0.0, 0.0, 0.0, fSpinBox->value());
}

void ManualScreen::extruderNegativeButtonClicked()
{

    emit relativeMove(0.0, 0.0, 0.0, m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal() * m_settings->value("motorsettings/extruder/multiplier", 3).toReal() * m_settings->value("motorsettings/stepsize", 64).toReal() * (-1.0), 0.0, 0.0, 0.0, fSpinBox->value());
}

void ManualScreen::homeButtonClicked()
{

    emit g28(true, true, true);
}

void ManualScreen::gcodeExecuteButtonClicked()
{

    emit gCodeCommand(ui->gcodeLine->text());
    ui->gcodeLine->clear();
}

void ManualScreen::stepsPerClickSpinBoxValueEdited(qreal value)
{

    m_settings->setValue("gui/manualscreen/stepsperclick", value);
}

void ManualScreen::xSpinBoxValueEdited(qreal value)
{

    emit absoluteMove(value, 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0, 0.0);
}

void ManualScreen::ySpinBoxValueEdited(qreal value)
{

    emit absoluteMove(0.0, value, 0.0, 0.0, 0.0, fSpinBox->value(), 0.0, 0.0);
}

void ManualScreen::zSpinBoxValueEdited(qreal value)
{

    emit absoluteMove(0.0, 0.0, value, 0.0, 0.0, 0.0, fSpinBox->value(), 0.0);
}

void ManualScreen::eSpinBoxValueEdited(qreal value)
{

    emit absoluteMove(0.0, 0.0, 0.0, value, 0.0, 0.0, 0.0, fSpinBox->value());
}

void ManualScreen::hotEndTargetTempSpinBoxValueEdited(qreal value)
{

    emit m104((int)(value));
}

void ManualScreen::bedTargetTempSpinBoxEdited(qreal value)
{

    emit m140((int)(value));
}

void ManualScreen::uiSetup()
{

    fSpinBox->resize(140, 40);
    stepsPerClickSpinBox->resize(140, 40);
    xSpinBox->resize(160, 40);
    ySpinBox->resize(160, 40);
    zSpinBox->resize(160, 40);
    eSpinBox->resize(160, 40);
    hotEndTargetTempSpinBox->resize(120, 40);
    bedTargetTempSpinBox->resize(120, 40);

    fSpinBox->move(309, 219);
    stepsPerClickSpinBox->move(309, 277);
    xSpinBox->move(539, 103);
    ySpinBox->move(539, 161);
    zSpinBox->move(539, 219);
    eSpinBox->move(539, 277);
    hotEndTargetTempSpinBox->move(220, 399);
    bedTargetTempSpinBox->move(579, 399);

    fSpinBox->setDecimals(3);
    stepsPerClickSpinBox->setDecimals(0);
    xSpinBox->setDecimals(5);
    ySpinBox->setDecimals(5);
    zSpinBox->setDecimals(5);
    eSpinBox->setDecimals(5);
    hotEndTargetTempSpinBox->setDecimals(1);
    bedTargetTempSpinBox->setDecimals(1);

    ui->manualControlCheckBox->setChecked(false);

    ui->xAxisPositiveButton->setEnabled(false);
    ui->xAxisNegativeButton->setEnabled(false);
    ui->yAxisPositiveButton->setEnabled(false);
    ui->yAxisNegativeButton->setEnabled(false);
    ui->zAxisPositiveButton->setEnabled(false);
    ui->zAxisNegativeButton->setEnabled(false);
    ui->extruderPositiveButton->setEnabled(false);
    ui->extruderNegativeButton->setEnabled(false);
    ui->homeButton->setEnabled(false);
    ui->gcodeExecuteButton->setEnabled(false);
    ui->gcodeLine->setEnabled(false);
    fSpinBox->setEnabled(false);
    stepsPerClickSpinBox->setEnabled(false);
    xSpinBox->setEnabled(false);
    ySpinBox->setEnabled(false);
    zSpinBox->setEnabled(false);
    eSpinBox->setEnabled(false);
    hotEndTargetTempSpinBox->setEnabled(false);
    bedTargetTempSpinBox->setEnabled(false);
}

void ManualScreen::uiUpdateSettings()
{

    fSpinBox->setMaximum(m_settings->value("gui/manualscreen/maxfeedrate", 2000.0).toReal());
    stepsPerClickSpinBox->setMaximum(m_settings->value("gui/manualscreen/maxstepsperclick", 10000.0).toReal());
    xSpinBox->setMaximum(m_settings->value("printer/xaxis/size", 400.0).toReal());
    ySpinBox->setMaximum(m_settings->value("printer/yaxis/size", 400.0).toReal());
    zSpinBox->setMaximum(m_settings->value("printer/zaxis/size", 400.0).toReal());
    eSpinBox->setMaximum(m_settings->value("gui/manualscreen/maxextrudersize", 1000000.0).toReal());
    hotEndTargetTempSpinBox->setMaximum(m_settings->value("heating/hotend/criticaltemp", 400.0).toReal());
    bedTargetTempSpinBox->setMaximum(m_settings->value("heating/bed/criticaltemp", 150.0).toReal());

    fSpinBox->setMinimum(0.0);
    stepsPerClickSpinBox->setMinimum(0.0);
    xSpinBox->setMinimum(m_settings->value("printer/xaxis/size", 400.0).toReal() * (-1.0));
    ySpinBox->setMinimum(m_settings->value("printer/yaxis/size", 400.0).toReal() * (-1.0));
    zSpinBox->setMinimum(m_settings->value("printer/zaxis/size", 400.0).toReal() * (-1.0));
    eSpinBox->setMinimum(m_settings->value("gui/manualscreen/maxextrudersize", 1000000.0).toReal() * (-1.0));
    hotEndTargetTempSpinBox->setMinimum(0.0);
    bedTargetTempSpinBox->setMinimum(0.0);

    fSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    stepsPerClickSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    xSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    ySpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    zSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    eSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    hotEndTargetTempSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());
    bedTargetTempSpinBox->setAutoRepeat(m_settings->value("gui/spinbox/autorepeat/on", true).toBool());

    fSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    stepsPerClickSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    xSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    ySpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    zSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    eSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    hotEndTargetTempSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());
    bedTargetTempSpinBox->setAutoRepeatDelay(m_settings->value("gui/spinbox/autorepeat/delay", 500).toInt());

    fSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    stepsPerClickSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    xSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    ySpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    zSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    eSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    hotEndTargetTempSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
    bedTargetTempSpinBox->setAutoRepeatInterval(m_settings->value("gui/spinbox/autorepeat/interval", 100).toInt());
}

void ManualScreen::uiUpdateValues()
{

    stepsPerClickSpinBox->setValue(m_settings->value("gui/manualscreen/stepsperclick", 10.0).toReal());
}
