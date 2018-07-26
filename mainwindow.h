#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Библиотеки устройств
#include "n9000a.h"                 //Класс Анализатора N9000
#include "gts.h"                 //Класс Анализатора GTS

#include <windowdevice.h>
#include <toolbox.h>

#include <windowachh.h>

#include <QThread>

#include <dialogseiting.h>
#include <screenn9000.h>

#include <QMessageBox>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ScreenN9000* screenN9000;
    N9000A*   N9000;
    GTS*      gts;

    DialogSeiting* dialogSeiting;

    QMessageBox* msgBox;






signals:
    void Work();

    void ConnectN9000(QString);

private slots:
    void END();
    void on_pushButton_clicked();

    void connectDevice(QString n9000, QString gts);

    void changListProverka(int);
    void changListProverka2(int,bool);

    void on_action_seitings_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
