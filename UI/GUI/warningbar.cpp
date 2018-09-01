#include "warningbar.h"
#include "ui_warningbar.h"

WarningBar::WarningBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningBar)
{
    ui->setupUi(this);

    m_warningIcon = new QSvgWidget(this);

    m_warningIcon->load(QString(":/Icons/UI/Icons/sharp-warning-24px.svg"));
    m_warningIcon->move(20, 20);
    m_warningIcon->resize(80, 80);

    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(on_okButtonClicked()));
}

WarningBar::~WarningBar()
{
    delete ui;
}

void WarningBar::paintEvent(QPaintEvent *pe) {

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void WarningBar::showWarning(QString warningMsg)
{

    ui->warningMsgBrowser->setText(warningMsg);
}

void WarningBar::on_okButtonClicked()
{

    emit okButtonClicked();
}
