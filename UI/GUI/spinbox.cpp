#include "spinbox.h"
#include "ui_spinbox.h"

SpinBox::SpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinBox)
{
    ui->setupUi(this);

    //initialising the pointers

    m_value = new qreal;
    m_prefix = new QString;
    m_suffix = new QString;
    m_minimum = new qreal;
    m_maximum = new qreal;
    m_stepSize = new qreal;
    m_decimals = new int;

    *m_value = 0.0;
    *m_minimum = 0.0;
    *m_maximum = 100.0;
    *m_stepSize = 1.0;
    *m_decimals = 3;

    //signals and slots

    //connecting the editingFinished signal of the valueLine to the valueLineEditingFinished slot of this SpinBox
    QObject::connect(ui->valueLine, SIGNAL(editingFinished()), this, SLOT(valueLineEditingFinished()));
    //connecting the clicked signal of the downButton to the downButtonClicked slot of this SpinBox
    QObject::connect(ui->downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));
    //connecting the clicked signal of the upButton to the upButtonClicked slot of this SpinBox
    QObject::connect(ui->upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));

    uiSetup();
    updateValueLineText();
}

SpinBox::~SpinBox()
{

    delete ui;
    delete m_value;
    delete m_prefix;
    delete m_suffix;
    delete m_minimum;
    delete m_maximum;
    delete m_stepSize;
    delete m_decimals;
}

void SpinBox::paintEvent(QPaintEvent *pe){

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

//changes the size of this Spinbox according to w and h
void SpinBox::resize(int w, int h)
{

    //checks if the given size is between the maximum and minimum size
    //triggered if it is
    if(QWidget::minimumWidth() <= w && QWidget::minimumHeight() <= h && QWidget::maximumWidth() >= w && QWidget::maximumHeight() >= h){

        //calls the resize function of QWidget so the size of the boundries changes
        QWidget::resize(w, h);
        //changes the the size sof the parts o fthis widget
        ui->valueLine->resize(w - (2 * h) + 1, h);
        ui->downButton->resize(h + 1, h);
        ui->upButton->resize(h, h);
        //moves the two buttons
        ui->downButton->move(ui->valueLine->width() - 1, 0);
        ui->upButton->move(ui->valueLine->width() + ui->downButton->width() - 2, 0);
    }
}

//changes the size of this Spinbox to s
void SpinBox::resize(const QSize &s)
{

    resize(s.width(), s.height());
}

//returns the value of m_value
qreal SpinBox::value()
{

    return *m_value;
}

//sets the value of maximum to maximum
void SpinBox::setMaximum(qreal maximum)
{

    //checks if the value of m_minimum is smaller than the value of maximum
    //triggerd if it is
    if(maximum > *m_minimum){

        *m_maximum = maximum;

        //checks if m_value needs to be fixed because of the change of m_maximum
        //triggered if it doesnt
        if(*m_value != fixValue(*m_value)){

            //writes the fixed value of m_value into m_value
            *m_value = fixValue(*m_value);
            //emits the valueChanged signal
            emit valueChanged(*m_value);
            //updates the text of the valueLine with prefix and suffix
            updateValueLineText();
        }
    }
}

//returns the value of m_maximum
qreal SpinBox::maximum()
{

    return *m_maximum;
}

//sets the value of m_minimum to minimum
void SpinBox::setMinimum(qreal minimum)
{

    //checks if the value of minimum is smaller than the value of m_maximum
    //triggerd if it is
    if(minimum < *m_maximum){

        *m_minimum = minimum;

        //checks if m_value needs to be fixed because of the change of m_minimum
        //triggered if it doesnt
        if(*m_value != fixValue(*m_value)){

            //writes the fixed value of m_value into m_value
            *m_value = fixValue(*m_value);
            //emits the valueChanged signal
            emit valueChanged(*m_value);
            //updates the text of the valueLine with prefix and suffix
            updateValueLineText();
        }
    }
}

//returns the value of m_minimum
qreal SpinBox::minimum()
{

    return *m_minimum;
}

//sets the value of m_stepSize to step
void SpinBox::setSingleStep(qreal step)
{

    *m_stepSize = step;
}

//returns the value of m_stepSize
qreal SpinBox::singleStep()
{

    return *m_stepSize;
}

//sets the value of m_prefix to prefix
void SpinBox::setPrefix(QString prefix)
{

    *m_prefix = prefix;
    //updates the text of the valueLine with prefix and suffix
    updateValueLineText();
}

QString SpinBox::prefix()
{

    return *m_prefix;
}

//sets the value of m_suffix to suffix
void SpinBox::setSuffix(QString suffix)
{

    *m_suffix = suffix;
    //updates the text of the valueLine with prefix and suffix
    updateValueLineText();
}

//returns the value of m_suffix
QString SpinBox::suffix()
{

    return *m_suffix;
}

//sets the value of m_decimals to decimals
void SpinBox::setDecimals(int decimals)
{

    *m_decimals = decimals;
}

//returns the value of m_decimals
int SpinBox::decimals()
{

    return *m_decimals;
}

//sets the value of m_value to value
void SpinBox::setValue(qreal value)
{

    //writes the fixed value of value into value
    value = fixValue(value);

    //checks if the value of m_value is equal to the value of value
    //triggered if it isnt
    if(*m_value != value){

        //writes the value of value into m_value
        *m_value = value;
        //updates the text of the valueLine with prefix and suffix
        updateValueLineText();
        //emits the valueChanged signal
        emit valueChanged(*m_value);
    }
}

//adds the value of m_stepSize to the value of m_value
void SpinBox::stepUp()
{

    setValue(*m_value + *m_stepSize);
}

//subtracts the value of m_stepSize from the value of m_value
void SpinBox::stepDown()
{

    setValue(*m_value - *m_stepSize);
}

//triggered if the clicked signal of the upButton is emitted
void SpinBox::upButtonClicked()
{

    //checks if the fixed value of(m_value + m_stepSize) is equal to the value of m_value
    //triggered if it isnt
    if(fixValue(*m_value + *m_stepSize) != *m_value){

        stepUp();
        //emits the valueEdited, because it isnt emitted by the stepUp function
        emit valueEdited(*m_value);
    }
}

//triggered if the clicked signal of the downButton is emitted
void SpinBox::downButtonClicked()
{

    //checks if the fixed value of(m_value - m_stepSize) is equal to the value of m_value
    //triggered if it isnt
    if(fixValue(*m_value - *m_stepSize) != *m_value){


        stepDown();
        //emits the valueEdited, because it isnt emitted by the stepDown function
        emit valueEdited(*m_value);
    }
}

//triggered if the editingFinished signal of the valueLine is emitted
void SpinBox::valueLineEditingFinished()
{

    //defining & initialising cal with the return value of checkValueLineText, so the value out of the text of valueLine
    qreal val = checkValueLineText();

    //writes the return value of fixValue(val) into val
    val = fixValue(val);

    //checks if val is different from the value of m_value
    //triggered if it is
    if(val != *m_value){

        *m_value = val;
        emit valueChanged(*m_value);
        emit valueEdited(*m_value);
    }

    //updates the text of the valueLine with prefix and suffix
    updateValueLineText();
}

//sets up the UI
void SpinBox::uiSetup()
{

    //sets the minimum size of this SpinBox
    QWidget::setMinimumHeight(30);
    QWidget::setMinimumWidth(90);
}

//checks the text of the valueLine for a valid number
//returns either the number or, if the number is invalid, the value of m_value
qreal SpinBox::checkValueLineText()
{

    //defining & initialising text with the text of valueLine
    QString text = ui->valueLine->text();
    qreal val;

    //checks if m_prefix is empty
    //triggered if it isnt
    if(m_prefix->isEmpty() == false){

        //removes the prefix from text
        text.remove(*m_prefix);
    }

    //checks if m_suffix is empty and if m_prefix and m_suffix are the same, so that if they are, the operation isnt done twice
    //triggered if it isnt empty and if m_prefix and m_suffix arent the same
    if(m_suffix->isEmpty() == false && *m_prefix != *m_suffix){

        //removes the suffix from text
        text.remove(*m_suffix);
    }

    //there to check if the conversion was successfull
    bool ok;
    //tries to convert text into a qreal and writes it into val
    val = (qreal)(text.toDouble(&ok));

    //checks if the above operation was successfull
    //triggered if was
    if(ok == true){

        return val;
    }

    return *m_value;
}

//fixes value if it is below the minimum or above the maximum
//returns the fixed value
qreal SpinBox::fixValue(qreal value)
{

    //checks if value is above the maximum or below the minimum
    //trigered if it is above the maximum
    if(value > *m_maximum){

        //sets value to maximum
        value = *m_maximum;
    }

    //triggered if it is below the minimum
    else if(value < *m_minimum){

        //sets value to the minimum
        value = *m_minimum;
    }

    return value;
}

//updates the text of the valueLine with prefix and suffix
void SpinBox::updateValueLineText()
{

    QString text;
    //defining & initialising digits with the value of m_decimals so that the decimals are taken into account
    int digits = *m_decimals;
    //defining & initialising help with the value of m_value so that the digits before the comma can be counted
    int help = (int)(*m_value);

    //counting the digits before the comma and adding them to digits
    //executed while the value of help bigger or equal to ten
    while(help >= 10){

        //deviding help by ten and saving it into help
        help = help / 10;
        digits++;
    }

    //adding 1 to digits so that the last digit is taken into account
    digits++;
    //appending the value of m_value to text
    text.append(QString::number(*m_value, 'g', digits));

    //appending a decimal pointto text, if there isnt one
    if(text.contains(QString(".")) == false){

        text.append(QString("."));
    }

    //appending zeros to text so the set number of decimals and the number of actual decimals match
    while(text.count() < digits + 1){

        text.append(QString("0"));
    }

    //inserting the prefix in the front of text
    text.insert(0, *m_prefix);
    //appending the suffix to text
    text.append(*m_suffix);
    //setting the text of valueLine to text
    ui->valueLine->setText(text);
}
