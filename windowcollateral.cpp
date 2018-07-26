#include "windowcollateral.h"
#include "ui_windowcollateral.h"

WindowCollateral::WindowCollateral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowCollateral)
{
    ui->setupUi(this);

    ui->label->setMinimumSize(100,250);
}

WindowCollateral::~WindowCollateral()
{
    delete ui;
}

void WindowCollateral::imgN9000(QPixmap *dataHtmlGet)
{
     ui->label->setPixmap(*dataHtmlGet);
}

/*
void WindowCollateral::imgN9000(QByteArray dataHtmlGet)
{
    QPixmap pix;

    pix.loadFromData(dataHtmlGet);

    ui->label->setPixmap(pix);
}
*/

void WindowCollateral::radioUpdate(int index, bool flag)
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

    switch (index) {

    case 1:
    {
        ui->radioButton->setStyleSheet(ss);
        break;
    }
    case 2:
    {
        ui->radioButton_2->setStyleSheet(ss);
        break;
    }

    }
}
