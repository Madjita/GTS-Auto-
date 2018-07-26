#include "windownes.h"
#include "ui_windownes.h"

WindowNes::WindowNes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowNes)
{
    ui->setupUi(this);

    ui->label->setMinimumSize(100,250);

}

WindowNes::~WindowNes()
{
    delete ui;
}

void WindowNes::imgN9000(QPixmap *dataHtmlGet)
{
     ui->label->setPixmap(*dataHtmlGet);
}

/*
void WindowNes::imgN9000(QByteArray dataHtmlGet)
{
    QPixmap pix;

    pix.loadFromData(dataHtmlGet);

    ui->label->setPixmap(pix);
}
*/

void WindowNes::radioUpdate(int freq, int index, bool flag)
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
                      ui->radioButton_8->setStyleSheet(ss);
                    break;
                }
                case 2:{
                     ui->radioButton_19->setStyleSheet(ss);
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
                  ui->radioButton_21->setStyleSheet(ss);
                break;
            }
            case 2:{
                 ui->radioButton_24->setStyleSheet(ss);
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
              ui->radioButton_25->setStyleSheet(ss);
            break;
        }
        case 2:{
             ui->radioButton_29->setStyleSheet(ss);
            break;
        }
        default:
            break;
        }
         break;
    }

    }
}
