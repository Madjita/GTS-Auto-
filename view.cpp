/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "view.h"
#include "callout.h"


#include <QDebug>



using namespace QtCharts;

View::View(QWidget *parent) :
    QChartView(parent),
    m_coordX(0),
    m_coordY(0),
    countSrv(0),
    m_chart(0),
    m_tooltip(0),
    m_isTouching(false)
{


    this->setMinimumSize(250,200);

   // setRubberBand(QChartView::RectangleRubberBand);


    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart();
    m_chart->setMinimumSize(100, 200); //не менять
    m_chart->setTitle("Наведите на линию, чтоб посмотреть точку. Нажмите на точку, чтоб зафиксировать просмотр.");
    m_chart->legend()->hide();

    m_scatter = new QScatterSeries();
    m_scatter->setName("scatter1");
    m_scatter->setMarkerSize(5);


   this->setChart(m_chart);

    series = new QLineSeries();



    qDebug () << series->points();



    m_chart->addSeries(m_scatter);
    m_chart->addSeries(series);



    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-90, 5);
    axisY->setLabelFormat("%i");
    axisY->setTitleText("dBm");
    series->attachAxis(axisY);
    m_scatter->attachAxis(axisY);


    m_chart->setAxisY(axisY, series);
    m_chart->setAxisY(axisY, m_scatter);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(900, 2200);
    axisX->setLabelFormat("%i");
    axisX->setTitleText("МГц");
    series->attachAxis(axisX);
    m_scatter->attachAxis(axisX);


    m_chart->setAxisX(axisX, series);
    m_chart->setAxisX(axisX, m_scatter);


    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);


    m_chart->resize(200,200);


    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(m_chart);
    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
    m_coordY->setText("Y: ");

    connect(series, &QLineSeries::clicked, this, &View::keepCallout);
    connect(series, &QLineSeries::hovered, this, &View::tooltip);

    this->setMouseTracking(true);


    srv = new QGraphicsSimpleTextItem(m_chart);

    srv->setText("Неравномерность: - Срывов: -");


}

void View::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
//![1]
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void View::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        m_chart->resize(event->size());
        m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 22);
        m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 22);
        srv->setPos(m_chart->size().width() - 220, m_chart->size().height() - 22);
        const auto callouts = m_callouts;
        for (Callout *callout : callouts)
            callout->updateGeometry();
    }


    QChartView::resizeEvent(event);
}

bool View::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{

    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos(),series).x()));
    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos(),series).y()));
    QChartView::mouseMoveEvent(event);
}

void View::keepCallout()
{
    m_callouts.append(m_tooltip);
    m_tooltip = new Callout(m_chart);
}

void View::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);

    if (state) {
        m_tooltip->setText(QString("X: %1 МГц\nY: %2 dBm").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}


void View::addPointGraph(double x, double y,double NeravnACHX)
{

    m_scatter->append(x,y);
    series->append(x,y);


    if(y <= -10)
    {
        countSrv++;
        srv->setText(QString("Неравномерность: %1 Срывов: %2").arg(NeravnACHX).arg(countSrv));

    }
    else
    {
        srv->setText(QString("Неравномерность: %1 Срывов: %2").arg(NeravnACHX).arg(countSrv));


    }


}

void View::clearGraph()
{
   series->clear();
   m_scatter->clear();

   srv->setText("Неравномерность: - Срывов: -");
   countSrv=0;
}
