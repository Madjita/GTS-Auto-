#ifndef WINDOWATTMAX_H
#define WINDOWATTMAX_H

#include <QWidget>

namespace Ui {
class WindowAttMax;
}

class WindowAttMax : public QWidget
{
    Q_OBJECT

public:
    explicit WindowAttMax(QWidget *parent = 0);
    ~WindowAttMax();

public slots:
    //void imgN9000(QByteArray html);

    void imgN9000(QPixmap *dataHtmlGet);

    void radioUpdate(int freq,bool flag);


private:
    Ui::WindowAttMax *ui;
};

#endif // WINDOWATTMAX_H
