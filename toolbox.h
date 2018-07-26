#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include <QPushButton>

////////////////////////////////////////////////
/// \brief The ToolItem class
///
class ToolItem : public QWidget {

    Q_OBJECT
public:
  explicit ToolItem(const QString &title, QWidget *item);


    QPushButton* titelLabel;

     void  OpenCloseWindow();

protected:
  void mousePressEvent(QMouseEvent *event);



private:
  QWidget *item;
};

/////////////////////////////////////////////////////////////////
/// \brief The ToolBox class
///
class ToolBox : public QWidget {

    Q_OBJECT

public:

    explicit ToolBox(QWidget *parent = nullptr);

  void addItem(ToolItem *item);

private:
  QVBoxLayout *layout;
};

#endif // TOOLBOX_H
