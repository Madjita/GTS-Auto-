#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    screenN9000(new ScreenN9000),
    N9000(new N9000A),
    gts(new GTS),
    dialogSeiting(new DialogSeiting(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gts->setN9000(N9000);


    QDateTime  date = QDateTime::currentDateTime();

    msgBox = new QMessageBox;

    this->setWindowTitle("GTS Auto [" + date.toLocalTime().toString() + "]");



    connect(this, &MainWindow::Work,gts,&GTS::Work);

    connect(gts, &GTS::imgUpdate,screenN9000,&ScreenN9000::imgN9000GetUpdate);
    connect(gts, &GTS::endProverk,this, &MainWindow::END);

    connect(dialogSeiting, &DialogSeiting::updateYSL,gts, &GTS::getUpdateYSL);

    dialogSeiting->setList();



    ui->listWidget->addItems(dialogSeiting->getList());

    ui->listWidget->setWordWrap(Qt::TextWrapAnywhere);


    for(int i=0; i < ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setIcon( QPixmap("://images/checkbox_unchecked.png"));
        ui->listWidget->item(i)->icon().setThemeName("://images/checkbox_unchecked.png");
    }


    connect(gts,&GTS::nextList,this,&MainWindow::changListProverka);

    connect(ui->windowDevice,&WindowDevice::deviceConnect,this,&MainWindow::connectDevice);
    connect(ui->windowDevice,&WindowDevice::deviceConnect,ui->windowAchHui,&WindowAchH::connectDevice);
    connect(ui->windowDevice,&WindowDevice::deviceConnect,screenN9000,&ScreenN9000::connectDevice);

    connect(ui->windowDevice , &WindowDevice::deviceDisconnect,N9000,&N9000A::DisConnect);
    connect(ui->windowDevice , &WindowDevice::deviceDisconnect,ui->windowAchHui,&WindowAchH::deviceDisconnect);
    connect(ui->windowDevice , &WindowDevice::deviceDisconnect,screenN9000,&ScreenN9000::deviceDisconnect);

    connect(screenN9000,&ScreenN9000::imgN9000,ui->windowAchHui,&WindowAchH::imgN9000Get);


    connect(this,&MainWindow::ConnectN9000,N9000,&N9000A::Connect);



    connect(gts,&GTS::addPointGraph,ui->windowAchHui,&WindowAchH::addPointGraph);
    connect(gts,&GTS::addPointGraph_GPRM,ui->windowAchHui_gprm,&WindowAchH::addPointGraph);

    connect(this, &MainWindow::Work,ui->windowAchHui,&WindowAchH::clearGraph);
    connect(this, &MainWindow::Work,ui->windowAchHui_gprm,&WindowAchH::clearGraph);

    connect(screenN9000,&ScreenN9000::imgN9000, ui->window10Khz,&Window10Khz::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowAttMax,&WindowAttMax::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowAttChenge,&WindowAttMax::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowCollateral,&WindowCollateral::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowSpectr,&WindowSpectr::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowNes,&WindowNes::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowAchHui_gprm,&WindowAchH::imgN9000Get);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->window10Khz_gprm,&Window10Khz::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowAttMax_gprm,&WindowAttMax::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowCollateral_gprm,&WindowCollateral::imgN9000);
    connect(screenN9000,&ScreenN9000::imgN9000, ui->windowSpectr_gprm,&WindowSpectr::imgN9000);





    connect(gts,&GTS::radioUpdate, ui->window10Khz,&Window10Khz::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka3, ui->windowAttMax,&WindowAttMax::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka4, ui->windowAttChenge,&WindowAttMax::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka5, ui->windowCollateral,&WindowCollateral::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka6, ui->windowSpectr,&WindowSpectr::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka7, ui->windowNes,&WindowNes::radioUpdate);
    connect(gts,&GTS::radioUpdate_GPRM, ui->window10Khz_gprm,&Window10Khz::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka3_GPRM, ui->windowAttMax_gprm,&WindowAttMax::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka5_GPRM, ui->windowCollateral_gprm,&WindowCollateral::radioUpdate);
    connect(gts,&GTS::radioUpdate_proverka6_GPRM, ui->windowSpectr_gprm,&WindowSpectr::radioUpdate);


    connect(gts,&GTS::next, ui->tabWidget,&QTabWidget::setCurrentIndex);
    connect(gts,&GTS::goodProverka, this,&MainWindow::changListProverka2);


    ui->tabWidget->setCurrentIndex(0);

    connect(dialogSeiting,&DialogSeiting::signal_list,gts,&GTS::updateProverkiListCheck);

    qRegisterMetaType<QList<bool>>("QList<bool>");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::END()
{
     msgBox->setText("Проверка блока завершена.");
     msgBox->exec();

}

void MainWindow::on_pushButton_clicked()
{

    emit Work();
}


void MainWindow::connectDevice(QString n9000Ip, QString gtsIp )
{
    gts->setIp(gtsIp);


    emit ConnectN9000(n9000Ip);
}

void MainWindow::changListProverka(int index)
{
    ui->listWidget->item(index)->setIcon( QPixmap("://images/checkbox_checked.png"));
    ui->listWidget->item(index)->icon().setThemeName("://images/checkbox_checked.png");
}

void MainWindow::changListProverka2(int index,bool flag)
{

    if(flag)
    {
        ui->listWidget->item(index)->setIcon( QPixmap("://images/checkbox_green.png"));
        ui->listWidget->item(index)->icon().setThemeName("://images/checkbox_green.png");
    }
    else
    {

        ui->listWidget->item(index)->setIcon( QPixmap("://images/checkbox_red.png"));
        ui->listWidget->item(index)->icon().setThemeName("://images/checkbox_red.png");
    }


}

void MainWindow::on_action_seitings_triggered()
{
    dialogSeiting->show();
}
