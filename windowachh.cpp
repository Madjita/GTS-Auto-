#include "windowachh.h"
#include "ui_windowachh.h"


WindowAchH::WindowAchH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowAchH)
{
    ui->setupUi(this);


    ui->tableView->setVisible(0);


    ui->label->setMinimumSize(100,250);



    flagSizeLabel = false;


    connect(this,&WindowAchH::addPointGraph,ui->chartView,&View::addPointGraph);

    connect(this,&WindowAchH::clearGraph,ui->chartView,&View::clearGraph);

}

WindowAchH::~WindowAchH()
{
    delete ui;
}


void WindowAchH::deviceDisconnect()
{
    emit clearGraph();

    n9000Ip = "";
    ui->label->clear();
    ui->label->setText("Устройство не подключенно");
}

void WindowAchH::connectDevice(QString n9000 , QString gts)
{

    emit clearGraph();

    n9000Ip = n9000;
}

void WindowAchH::imgN9000Get(QPixmap *dataHtmlGet)
{
    ui->label->setPixmap(*dataHtmlGet);
}

/*void WindowAchH::imgN9000Get(QByteArray dataHtmlGet)
{

    QPixmap pix;

    pix.loadFromData(dataHtmlGet);


    ui->label->setPixmap(pix);
}*/
