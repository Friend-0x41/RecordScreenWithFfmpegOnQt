#include "selectrectwidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QColor>
#include <QPen>
#include <QRect>
#include <QScreen>
#include <QDebug>

SelectRectWidget::SelectRectWidget(QWidget *parent) : QWidget(parent)
{
    initWindow();
    loadBackGroundPixmap();
    m_isMouserPress =false;
    this->setAttribute(Qt::WA_DeleteOnClose);
}

SelectRectWidget::~SelectRectWidget()
{
    qDebug() << "Destroy";
}

void SelectRectWidget::initWindow()
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

void SelectRectWidget::loadBackGroundPixmap()
{
    m_loadPixmap = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    m_screenWidth = m_loadPixmap.width();
    m_screenHeight = m_loadPixmap.height();
}

void SelectRectWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isMouserPress = true;
        m_beginPoint = event->pos();
    }
    else if(event->button() == Qt::RightButton)
    {
        QRect rect = this->getRect(m_beginPoint,m_endPoint);
        if (rect.contains(event->pos()))
        {
            emit completeSelect(rect);
            close();
        }
        else
        {
            close();
        }
    }
    return QWidget::mousePressEvent(event);
}

void SelectRectWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isMouserPress)
    {
        m_endPoint = event->pos();
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void SelectRectWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_endPoint == event->pos();
        m_isMouserPress = false;
    }
    return QWidget::mouseReleaseEvent(event);
}

void SelectRectWidget::paintEvent(QPaintEvent *event)
{
    m_painter.begin(this);
    QColor shadowColor = QColor(0,0,0,100);
    m_painter.setPen(QPen(Qt::red,1,Qt::SolidLine,Qt::FlatCap));
    m_painter.drawPixmap(0,0,m_loadPixmap);
    m_painter.fillRect(m_loadPixmap.rect(),shadowColor);
    if(m_isMouserPress)
    {
        QRect selectRect = this->getRect(m_beginPoint,m_endPoint);
        m_capturePixmap = m_loadPixmap.copy(selectRect);
        m_painter.drawPixmap(selectRect.topLeft(),m_capturePixmap);
        m_painter.drawRect(selectRect);
    }
    m_painter.end();
}

void SelectRectWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        QRect rect = this->getRect(m_beginPoint,m_endPoint);
        emit completeSelect(rect);
        close();
    }
}

QRect SelectRectWidget::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x,y,width,height;
    width = qAbs(beginPoint.x() -endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = qMin(beginPoint.x(),endPoint.x());
    y = qMin(beginPoint.y(),endPoint.y());
    QRect rect = QRect(x,y,width,height);
    if(rect.width() == 0)
    {
        rect.setWidth(1);
    }
    if(rect.height() == 0)
    {
        rect.setHeight(1);
    }
    if(rect.width() % 2 != 0)
    {
        rect.setWidth(rect.width() + 1);
    }
    if(rect.height() % 2 != 0)
    {
        rect.setHeight(rect.height() + 1);
    }
    return rect;
}
