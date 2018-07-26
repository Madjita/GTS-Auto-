#ifndef WINDOWNES_H
#define WINDOWNES_H

#include <QWidget>

namespace Ui {
class WindowNes;
}

class WindowNes : public QWidget
{
    Q_OBJECT

public:
    explicit WindowNes(QWidget *parent = 0);
    ~WindowNes();


public slots:
    //void imgN9000(QByteArray html);

    void imgN9000(QPixmap *dataHtmlGet);

    void radioUpdate(int freq,int index,bool flag);

private:
    Ui::WindowNes *ui;
};

#endif // WINDOWNES_H

