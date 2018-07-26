#ifndef WINDOWFINDDEVICE_H
#define WINDOWFINDDEVICE_H

#include <visa.h>

#include <QWidget>
#include <QDebug>
#include <QStandardItemModel>
#include <QHostInfo>

namespace Ui {
class WindowFindDevice;
}

class WindowFindDevice : public QWidget
{
    Q_OBJECT

public:
    explicit WindowFindDevice(QWidget *parent = 0);
    ~WindowFindDevice();

    ViSession vi;
    ViSession viDevice;
    int viStatus;
    ViRsrc viAddres;
    bool connected;
    ViSession defaultRM;


private slots:
    void on_pushButton_clicked();

    QString query_IDN(ViSession vi);

private:
    Ui::WindowFindDevice *ui;
};

#endif // WINDOWFINDDEVICE_H
