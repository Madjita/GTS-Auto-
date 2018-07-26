#include "windowfinddevice.h"
#include "ui_windowfinddevice.h"

#include <QTextCodec>
#include <QMessageBox>

WindowFindDevice::WindowFindDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowFindDevice)
{
    ui->setupUi(this);
}

WindowFindDevice::~WindowFindDevice()
{
    delete ui;
}

void WindowFindDevice::on_pushButton_clicked()
{
    viStatus = viOpenDefaultRM(&defaultRM);

    unsigned long countDevice = 0;

    char  buff[100];

    for(int i=0;i < 100;i++)
    {
        buff[i] = NULL;
    }


    QList<QString> *listDevice = new QList<QString>;

    QList<QString> *listDeviceName = new QList<QString>;

    QStringList razbor ;


    viStatus = viFindRsrc(defaultRM, ViString("TCPIP?*"), &vi , &countDevice, buff);


    ui->tableWidget->setRowCount(static_cast<int>(countDevice));
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);

    if(static_cast<int>(countDevice) == 0 )
    {
        QMessageBox msgBox;
        msgBox.setText("Устройства не найдены.");
        msgBox.exec();
    }
    else
    {

        for(int i=0; i <  static_cast<int>(countDevice);i++)
        {

            QString strBuff(qPrintable(buff));

            char mass[50];





            mass[0] = buff[strBuff.count()+2];

            int count = 0;

            do
            {
                count++;
                mass[count] =  buff[strBuff.count()+2+count];

            }while(mass[count] != '\0' );


            QString  strBuff2 = QString::fromLocal8Bit(mass);



            razbor = strBuff2.split("\t");


            for(int i=0;i < 100;i++)
            {
                buff[i] = NULL;
            }



            if(strBuff.split(':').last() == "SOCKET")
            {
                strBuff += "::GEN";
            }

            if(razbor.value(1).split(' ').first() == "N9030A")
            {
                QString hostNameNumber = razbor.value(1).split(' ').last();
                hostNameNumber.remove(0,5);


                QString hostName = "A-"+razbor.value(1).split(' ').first() +"-"+ hostNameNumber +".local";

                auto str =  QHostInfo::fromName(hostName);

                qDebug () << str.addresses().value(0).toString();

                strBuff = "TCPIP::" + str.addresses().value(0).toString() + "::inst0::INSTR";
            }


            qDebug ()  << strBuff.split(':');


            listDevice->append(strBuff.split(':').value(2));


            //   viStatus = viOpen(defaultRM,  ViRsrc(qPrintable(strBuff)), ViAccessMode(VI_NULL),ViUInt32(VI_NULL),&viDevice);


            listDeviceName->append(razbor.value(1));


            viClose(viDevice);

            viStatus = viFindNext(vi,buff);



            ui->tableWidget->setItem(i,1,new QTableWidgetItem(listDevice->value(i)));
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(listDeviceName->value(i)));

            if(razbor.value(0) == "")
            {
                ui->tableWidget->setItem(i,2,new QTableWidgetItem("Свободен"));
            }
            else
            {
                ui->tableWidget->setItem(i,2,new QTableWidgetItem("Занят"));
            }


        }
    }



    viClose(vi);
    viClose(defaultRM);





}

//Команда на проверку ошибок в запросе
QString WindowFindDevice::query_IDN(ViSession vi)
{
    char buff[1024] = "";

    viQueryf(vi,ViString("*IDN?\n"),ViString("%T"),buff);


    return qPrintable(buff);

}
