#ifndef WINDOWSPECTR_H
#define WINDOWSPECTR_H

#include <QWidget>

namespace Ui {
class WindowSpectr;
}

class WindowSpectr : public QWidget
{
    Q_OBJECT

public:
    explicit WindowSpectr(QWidget *parent = 0);
    ~WindowSpectr();

public slots:
   // void imgN9000(QByteArray html);

    void imgN9000(QPixmap *dataHtmlGet);

    void radioUpdate(int freq,int index,bool flag);

private:
    Ui::WindowSpectr *ui;
};

#endif // WINDOWSPECTR_H
