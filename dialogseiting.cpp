#include "dialogseiting.h"
#include "ui_dialogseiting.h"

#include <QModelIndex>
#include <QFile>

DialogSeiting::DialogSeiting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeiting)
{


    ui->setupUi(this);

    qDebug () <<QCoreApplication::applicationDirPath()  + "/seitings.txt";

    QFile file(QCoreApplication::applicationDirPath()  + "/seitings.txt");
    if (file.open(QFile::ReadOnly))
    {
        QString line = file.readLine(200);
        QStringList list = line.simplified().split(',');
        ui->tableWidget->setColumnCount(list.count());
        ui->tableWidget->setHorizontalHeaderLabels(list);
        ui->tableWidget->resizeColumnToContents(0);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget->verticalHeader()->setVisible(false);


        int row = 0;

        while (file.canReadLine()) {
            line = file.readLine(300);
            list = line.simplified().split(',');


            if(row == 5 || row == 4 )
            {
                qDebug () << "dsfasd";
            }

            if(list.count() == 2 || list.count() == 3)
            {
                ui->tableWidget->setRowCount(row+1);

                QTableWidgetItem *nameItem = new QTableWidgetItem(line);

                ui->tableWidget->setItem(row, 0, nameItem);

            }
            else
            {
                if(list.count() == 5)
                {
                    for(int i =0 ; i < list.count(); i++)
                    {
                        QTableWidgetItem *Item = new QTableWidgetItem(list.value(i));

                        ui->tableWidget->setItem(row, i+1, Item);
                    }

                    row++;
                }
            }


        }

    }
    file.close();


    emit updateYSL(getListYSL_Nominal(),getListYSL_pred_otkl(),getListYSL_pred_znach(),getListYSL_prim());

}

DialogSeiting::~DialogSeiting()
{
    delete ui;
}

QStringList DialogSeiting::getList()
{
    QStringList list;


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {

        list.append(ui->tableWidget->item(row,0)->text());

    }

    return list;

}

QStringList DialogSeiting::getListYSL_Nominal()
{
    QStringList list;


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {

        list.append(ui->tableWidget->item(row,1)->text());

    }

    return list;
}

QStringList DialogSeiting::getListYSL_pred_otkl()
{
    QStringList list;


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {

        list.append(ui->tableWidget->item(row,2)->text());

    }

    return list;
}

QStringList DialogSeiting::getListYSL_pred_znach()
{
    QStringList list;


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {

        list.append(ui->tableWidget->item(row,3)->text());

    }

    return list;
}

QStringList DialogSeiting::getListYSL_prim()
{
    QStringList list;


    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {

        list.append(ui->tableWidget->item(row,5)->text());

    }

    return list;
}

void DialogSeiting::setList()
{

    emit updateYSL(getListYSL_Nominal(),getListYSL_pred_otkl(),getListYSL_pred_znach(),getListYSL_prim());

}

void DialogSeiting::on_buttonBox_accepted()
{
    QList<bool> list;

    list.append(ui->checkBox->isChecked());
    list.append(ui->checkBox_2->isChecked());
    list.append(ui->checkBox_3->isChecked());
    list.append(ui->checkBox_4->isChecked());
    list.append(ui->checkBox_5->isChecked());
    list.append(ui->checkBox_6->isChecked());
    list.append(ui->checkBox_7->isChecked());
    list.append(ui->checkBox_8->isChecked());
    //list.append(ui->checkBox_9->isChecked());
   // list.append(ui->checkBox_10->isChecked());
    list.append(ui->checkBox_11->isChecked());
    //list.append(ui->checkBox_12->isChecked());
    list.append(ui->checkBox_13->isChecked());
    list.append(ui->checkBox_14->isChecked());
    list.append(ui->checkBox_15->isChecked());
    list.append(ui->checkBox_16->isChecked());
    list.append(ui->checkBox_17->isChecked());
    list.append(ui->checkBox_18->isChecked());


    emit signal_list(list);
}
