#ifndef WINDOWCOLLATERAL_H
#define WINDOWCOLLATERAL_H

#include <QWidget>

namespace Ui {
class WindowCollateral;
}

class WindowCollateral : public QWidget
{
    Q_OBJECT

public:
    explicit WindowCollateral(QWidget *parent = 0);
    ~WindowCollateral();

public slots:
   // void imgN9000(QByteArray html);

    void radioUpdate(int index,bool flag);

    void imgN9000(QPixmap *dataHtmlGet);

private:
    Ui::WindowCollateral *ui;
};

#endif // WINDOWCOLLATERAL_H
