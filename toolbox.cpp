#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent),
     layout(new QVBoxLayout)
{

   setLayout(layout);

}

void ToolBox::addItem(ToolItem *item) {
    // Remove last spacer item if present.
    int count = layout->count();

    if (count > 1)
    {
        layout->removeItem(layout->itemAt(count - 1));
    }

    // Add item and make sure it stretches the remaining space.
    layout->addWidget(item);
    layout->addStretch();
}

ToolItem::ToolItem(const QString &title, QWidget *item) :
    item(item)
{

    QVBoxLayout *layout = new QVBoxLayout;

    titelLabel = new QPushButton(title);

    connect(titelLabel,&QPushButton::clicked,this,&ToolItem::OpenCloseWindow);



   const char stylesheet[] =
        "QPushButton{"
        "background-color: grey;"
        "border-style: outset;"
        "border-width: 2px;"
        "border-radius: 10px;"
        "border-color: beige;"
        "font: bold 14px;"
        "min-width: 10em;"
        "padding: 6px;}"
        "QPushButton:pressed{"
        "background-color: rgb(169,169,169);"
        "border-style: inset;}";


    titelLabel->setStyleSheet(stylesheet);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(titelLabel);
    layout->addWidget(item);

    setLayout(layout);

    item->setVisible(false);
}

void ToolItem::mousePressEvent(QMouseEvent *event) {

    Q_UNUSED(event);

    item->setVisible(!item->isVisible());
}

void ToolItem::OpenCloseWindow()
{
    item->setVisible(!item->isVisible());
}
