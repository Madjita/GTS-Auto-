#include "window10khz.h"
#include "ui_window10khz.h"

Window10Khz::Window10Khz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window10Khz)
{
    ui->setupUi(this);

    ui->label->setMinimumSize(100,250);
}

Window10Khz::~Window10Khz()
{
    delete ui;
}

/*
void Window10Khz::imgN9000(QByteArray dataHtmlGet)
{

    QPixmap pix;

    pix.loadFromData(dataHtmlGet);


    ui->label->setPixmap(pix);
}
*/

void Window10Khz::imgN9000(QPixmap *dataHtmlGet)
{
    ui->label->setPixmap(*dataHtmlGet);
}

void Window10Khz::radioUpdate(int freq, bool flag)
{
    QString ss;

    if(flag)
    {
        ss =
                "QRadioButton::indicator{"
                "width: 13px;"
                " height: 13px;"
                "}"
                "QRadioButton::indicator::unchecked{"
                "image: url(://images/circle_zel.png);"
                "}"
                "QRadioButton::indicator::checked{"
                "image: url(://images/circle_zel.png);"
                "}";
    }
    else
    {
        ss =
                "QRadioButton::indicator{"
                "width: 13px;"
                " height: 13px;"
                "}"
                "QRadioButton::indicator::unchecked{"
                "image: url(://images/circle_kras.png);"
                "}"
                "QRadioButton::indicator::checked{"
                "image: url(://images/circle_kras.png);"
                "}";
    }

    switch (freq) {

    case 950:
    {
        ui->radioButton->setStyleSheet(ss);
        break;
    }
    case 1250:
    {
        ui->radioButton_2->setStyleSheet(ss);
        break;
    }
    case 1500:
    {
        ui->radioButton_3->setStyleSheet(ss);
        break;
    }
    case 1750:
    {
        ui->radioButton_4->setStyleSheet(ss);
        break;
    }
    case 2000:
    {
        ui->radioButton_5->setStyleSheet(ss);
        break;
    }
    case 2150:
    {
        ui->radioButton_6->setStyleSheet(ss);
        break;
    }

    }


}
