#ifndef WINDOWDEVICE_H
#define WINDOWDEVICE_H

#include <QWidget>

#include <windowfinddevice.h>

namespace Ui {
class WindowDevice;
}

class WindowDevice : public QWidget
{
    Q_OBJECT

public:
    explicit WindowDevice(QWidget *parent = 0);
    ~WindowDevice();


    WindowFindDevice* windowFindDevice;

signals:
    void deviceConnect(QString , QString);
    void deviceDisconnect();

private slots:
    void on_pushButton_deviceConnect_clicked();



    void on_pushButton_deviceDicconnect_clicked();

    void on_pushButton_clicked();

private:
    Ui::WindowDevice *ui;
};

#endif // WINDOWDEVICE_H
