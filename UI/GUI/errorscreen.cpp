#include "errorscreen.h"
#include "ui_errorscreen.h"

ErrorScreen::ErrorScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorScreen)
{
    ui->setupUi(this);

    m_errorIcon = new QSvgWidget(this);

    m_errorIcon->load(QString(":/Icons/UI/Icons/sharp-error_outline-24px.svg"));
    m_errorIcon->move(40, 40);
    m_errorIcon->resize(256, 256);
}

ErrorScreen::~ErrorScreen()
{
    delete ui;
}

void ErrorScreen::paintEvent(QPaintEvent *pe) {

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void ErrorScreen::showError(int code, QString message)
{

    QString hexcode = convertDecToHex(code);

    ui->errorMsgBrowser->setText(message);
    ui->errorValueLabel->setText(hexcode);
}

void ErrorScreen::on_okButtonClicked()
{

    emit okButtonClicked();
}

QString ErrorScreen::convertDecToHex(int decimal)
{

    //defining the output variable
    QString hexcode;

    //converting from decimal to hexadecimal
    hexcode.setNum(decimal, 16);

    //filling the string hexcode up with 0s up to the 6th digit
    for(int i = hexcode.count();i < 6;i++){

        //puts a 0 at the first place of the string hexcode
        hexcode.insert(0, QString("0"));
    }

    //replaces the small letters with capital letters
    for(int i = 0;i < hexcode.count();i++){

        //checks if the letter in hexcode at i is a small letter
        //triggerd if it is
        if(hexcode.unicode()[i].unicode() > 96 && hexcode.unicode()[i].unicode() < 123){

            //converts it to a capital letter and writes it into hexcode at i
            hexcode.replace(i, 1, QChar(hexcode.unicode()[i].unicode() - 32));
        }
    }

    return hexcode;
}
