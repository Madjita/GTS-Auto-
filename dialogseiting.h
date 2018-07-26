#ifndef DIALOGSEITING_H
#define DIALOGSEITING_H

#include <QDialog>
#include <QDebug>
#include <QListWidget>
#include <QTableWidgetItem>

namespace Ui {
class DialogSeiting;
}

class DialogSeiting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeiting(QWidget *parent = 0);
    ~DialogSeiting();

    QStringList getList();


    QStringList getListYSL_Nominal();
    QStringList getListYSL_pred_otkl();
    QStringList getListYSL_pred_znach();
    QStringList getListYSL_prim();


    void setList();


signals:
    void updateYSL(QStringList,QStringList,QStringList,QStringList);

    void signal_list(QList<bool> list);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogSeiting *ui;
};

#endif // DIALOGSEITING_H
