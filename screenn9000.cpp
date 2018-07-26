#include "screenn9000.h"

ScreenN9000::ScreenN9000()
{
    this->moveToThread(new QThread());

    connect(this->thread(),&QThread::started,this,&ScreenN9000::process_start);

    this->thread()->start();
}

ScreenN9000::~ScreenN9000()
{

}

void ScreenN9000::process_start()
{

    manager = new QNetworkAccessManager(this);


    flagSizeLabel = false;
    timer = new QTimer();


    connect(timer,&QTimer::timeout,this,&ScreenN9000::getScreen);

    connect(this,SIGNAL(timerStart()),timer,SLOT(start()));
    connect(this,SIGNAL(timerStart(int)),timer,SLOT(start(int)));
    connect(this,&ScreenN9000::timerStop,timer,&QTimer::stop);

    pix = new QPixmap;


}


void ScreenN9000::replyFinished(QNetworkReply *reply)
{
    if( reply->error() == QNetworkReply::NoError )
    {

        QByteArray dataHtml = reply->readAll();

        pix->loadFromData(dataHtml);

        emit imgN9000(pix);


    }
    else
    {
        //  qDebug() << reply->errorString();

    }

    // Мы сами должны освободить память для reply
    // Однако делать это через delete нельзя
    reply->deleteLater();
}

void ScreenN9000::getScreen()
{
    manager->get(QNetworkRequest(QUrl("http://"+n9000Ip+"/Agilent.SA.WebInstrument/Screen.png")));

}

void ScreenN9000::connectDevice(QString n9000 , QString gts)
{
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    emit timerStop();
    n9000Ip = n9000;

    emit timerStart(200);
}

void ScreenN9000::deviceDisconnect()
{
     emit timerStop();

    disconnect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(replyFinished(QNetworkReply*)));


    n9000Ip = "";

}

void ScreenN9000::imgN9000GetUpdate()
{
   emit   getScreen();
}
