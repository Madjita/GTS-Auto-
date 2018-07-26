#include "windowattmax.h"
#include "ui_windowattmax.h"

WindowAttMax::WindowAttMax(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowAttMax)
{
    ui->setupUi(this);

     ui->label->setMinimumSize(100,250);
}

WindowAttMax::~WindowAttMax()
{
    delete ui;
}

void WindowAttMax::imgN9000(QPixmap *dataHtmlGet)
{
     ui->label->setPixmap(*dataHtmlGet);
}


/*void WindowAttMax::imgN9000(QByteArray dataHtmlGet)
{

    QPixmap pix;

    pix.loadFromData(dataHtmlGet);


    ui->label->setPixmap(pix);
}*/

void WindowAttMax::radioUpdate(int freq, bool flag)
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
    case 1550:
    {
        ui->radioButton_3->setStyleSheet(ss);
        break;
    }
    case 2150:
    {
        ui->radioButton_6->setStyleSheet(ss);
        break;
    }

    }
}
