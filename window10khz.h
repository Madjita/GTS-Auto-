#ifndef WINDOW10KHZ_H
#define WINDOW10KHZ_H

#include <QWidget>

#include<QPixmap>
#include<QDebug>

namespace Ui {
class Window10Khz;
}

class Window10Khz : public QWidget
{
    Q_OBJECT

public:
    explicit Window10Khz(QWidget *parent = 0);
    ~Window10Khz();


public slots:
   // void imgN9000(QByteArray html);

    void imgN9000(QPixmap *dataHtmlGet);

    void radioUpdate(int freq,bool flag);

private:
    Ui::Window10Khz *ui;
};

#endif // WINDOW10KHZ_H
