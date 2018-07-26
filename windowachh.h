#ifndef WINDOWACHH_H
#define WINDOWACHH_H

#include <QWidget>

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





namespace Ui {
class WindowAchH;
}

class WindowAchH : public QWidget
{
    Q_OBJECT

public:
    explicit WindowAchH(QWidget *parent = 0);
    ~WindowAchH();

    QByteArray dataHtml;

    bool flagSizeLabel;

    QString n9000Ip;



public slots:

    void deviceDisconnect();
    void connectDevice(QString n9000, QString gts);

    //void imgN9000Get(QByteArray dataHtmlGet);
    void imgN9000Get(QPixmap* dataHtmlGet);

signals:
     void addPointGraph( double x, double y,double NeravnACHX);

     void clearGraph();


     void imgN9000(QByteArray dataHtml);






private:
    Ui::WindowAchH *ui;
};

#endif // WINDOWACHH_H
