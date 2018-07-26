#ifndef GTS_H
#define GTS_H

#include <QObject>

#include <QThread>
#include <QString>
#include <QTextEdit>
#include <QApplication>
#include <QtNetwork>

#include <n9000a.h>
#include <windows.h>

#include <QPoint>
#include<QVariant>
#include <QList>



class GTS : public QObject
{
    Q_OBJECT
public:
    explicit GTS(QObject *parent = nullptr);


    ~GTS();

     N9000A*   N9000;

     int  GnFREQuencyStart;
     int  GnFREQuencyEnd;
     int  GnFREQuencyStep;
     int  GnFREQuencyStep_kHz;
     int  GnPower;

     QVector<double> x;
     QVector<double> y;


     QStringList ListYSL_Nominal;
     QStringList ListYSL_pred_otkl;
     QStringList ListYSL_pred_znach;
     QStringList ListYSL_prim;

    QList<bool> listProverka;


signals:
    void endProverk();
    void log(QString);

    void imgUpdate();

    void addPointGraph( double x, double y,double NeravnACHX);
    void addPointGraph_GPRM( double x, double y,double NeravnACHX);

    void radioUpdate(int freq, bool flag);
    void radioUpdate_GPRM(int freq, bool flag);

    void radioUpdate_proverka3(int freq, bool flag);
    void radioUpdate_proverka3_GPRM(int freq, bool flag);

    void radioUpdate_proverka4(int freq, bool flag);

    void radioUpdate_proverka5(int index, bool flag);
    void radioUpdate_proverka5_GPRM(int index, bool flag);

    void radioUpdate_proverka6(int freq,int index, bool flag);
    void radioUpdate_proverka6_GPRM(int freq,int index, bool flag);

    void radioUpdate_proverka7(int freq,int index, bool flag);

    void next(int);
    void nextList(int);

    void goodProverka(int,bool);

public slots:
    void setIp(QString ip);
    void setN9000(N9000A* get_N9000);
    void write(int status_izl, int att, int freq_prd, int uhf_prd,int dopler_prd, int freq_prm, int uhf_prm, int dopler_prm, int freq_dds, int ampl_i, int ampl_qm ,int ph_i ,int ph_q, int offset_i, int offset_q);
    void process_start();

    void updateProverkiListCheck(QList<bool> list);


    void stepPoint_n9000(int end);
    void getPoint_n9000(double& dResultX,double& dResultY);

    void getUpdateYSL(QStringList getListYSL_Nominal,QStringList gretListYSL_pred_otkl,QStringList getListYSL_pred_znach,QStringList getListYSL_prim);


    void Work();
    void proverka_1();
    void proverka_2();
    void proverka_3();
    void proverka_4();
    void proverka_5();
    void proverka_6();
    void proverka_7();
    void proverka_8();
    void proverka_9();
    void proverka_10();
    void proverka_11();
    void proverka_12();
    void proverka_13();
    void proverka_14();
    void proverka_15();

private:
    QUdpSocket *m_pUdpSocket, *p_udpSocketIn;
    QString ip_addr;
};

#endif // GTS_H
