#include "windowdevice.h"
#include "ui_windowdevice.h"

WindowDevice::WindowDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowDevice)
{
    ui->setupUi(this);

    this->setMinimumSize(100,100);
}

WindowDevice::~WindowDevice()
{
    delete ui;
}

void WindowDevice::on_pushButton_deviceConnect_clicked()
{
    emit deviceConnect(ui->lineEdit->text(),ui->lineEdit_2->text());
}


void WindowDevice::on_pushButton_deviceDicconnect_clicked()
{
    emit deviceDisconnect();
}

void WindowDevice::on_pushButton_clicked()
{

    windowFindDevice = new WindowFindDevice();

    windowFindDevice->show();
}
