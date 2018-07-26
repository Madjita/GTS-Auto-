#ifndef SCREENN9000_H
#define SCREENN9000_H

#include <QObject>

#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include <QtCharts/QtCharts>

#include <QNetworkAccessManager>
#include <QDebug>
#include <QNetworkReply>

#include <QTimer>


class ScreenN9000: public QObject
{
     Q_OBJECT

public:
    ScreenN9000();
    ~ScreenN9000();

    QTimer* timer;
    bool flagSizeLabel;

    QString n9000Ip;

    QNetworkAccessManager *manager;

    QPixmap* pix;

public slots:
     void process_start();

     void getScreen();

     void replyFinished(QNetworkReply *reply);

     void connectDevice(QString n9000 , QString gts);
     void deviceDisconnect();

     void imgN9000GetUpdate();

signals:
     void imgN9000(QPixmap* dataHtmlGet);

     void timerStart(int msec);
     void timerStart();

     void timerStop();


};

#endif // SCREENN9000_H
