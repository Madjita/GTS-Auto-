#include "windowspectr.h"
#include "ui_windowspectr.h"

WindowSpectr::WindowSpectr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowSpectr)
{
    ui->setupUi(this);

    ui->label->setMinimumSize(100,250);
}

WindowSpectr::~WindowSpectr()
{
    delete ui;
}

void WindowSpectr::imgN9000(QPixmap *dataHtmlGet)
{
    ui->label->setPixmap(*dataHtmlGet);
}

/*
void WindowSpectr::imgN9000(QByteArray dataHtmlGet)
{
    QPixmap pix;

    pix.loadFromData(dataHtmlGet);

    ui->label->setPixmap(pix);
}
*/

void WindowSpectr::radioUpdate(int freq,int index,bool flag)
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

                switch (index) {
                case 1:{
                      ui->radioButton->setStyleSheet(ss);
                    break;
                }
                case 2:{
                     ui->radioButton_1->setStyleSheet(ss);
                    break;
                }
                case 3:{
                     ui->radioButton_3->setStyleSheet(ss);
                    break;
                }
                case 4:{
                     ui->radioButton_6->setStyleSheet(ss);
                    break;
                }
                case 5:{
                     ui->radioButton_7->setStyleSheet(ss);
                    break;
                }
                default:
                    break;
                }




        break;
    }
    case 1550:
    {

                switch (index) {
                case 1:{
                      ui->radioButton_2->setStyleSheet(ss);
                    break;
                }
                case 2:{
                     ui->radioButton_4->setStyleSheet(ss);
                    break;
                }
                case 3:{
                     ui->radioButton_10->setStyleSheet(ss);
                    break;
                }
                case 4:{
                     ui->radioButton_9->setStyleSheet(ss);
                    break;
                }
                case 5:{
                     ui->radioButton_11->setStyleSheet(ss);
                    break;
                }
                default:
                    break;
                }

        break;
    }
    case 2150:
    {
                switch (index) {
                case 1:{
                      ui->radioButton_5->setStyleSheet(ss);
                    break;
                }
                case 2:{
                     ui->radioButton_15->setStyleSheet(ss);
                    break;
                }
                case 3:{
                     ui->radioButton_13->setStyleSheet(ss);
                    break;
                }
                case 4:{
                     ui->radioButton_12->setStyleSheet(ss);
                    break;
                }
                case 5:{
                     ui->radioButton_14->setStyleSheet(ss);
                    break;
                }
                default:
                    break;
                }
         break;
    }

    }
}
